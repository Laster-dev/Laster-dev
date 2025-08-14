# Minimal Shellcode Loader Makefile
# Uses only Windows API, no CRT

CC=gcc
TARGET=shellcode_loader.exe
TARGET_MINI=shellcode_loader_mini.exe
SOURCE=shellcode_loader.c
SOURCE_MINI=shellcode_loader_mini.c

# Compiler flags for minimal binary
CFLAGS=-Os -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident -fdata-sections -ffunction-sections
LDFLAGS=-nostdlib -nostartfiles -s -Wl,--gc-sections -Wl,--strip-all -Wl,--no-seh
LIBS=-lkernel32 -lwininet

# Default target - build both versions
all: x64 x64-mini

# Standard version
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

# Mini version
$(TARGET_MINI): $(SOURCE_MINI)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET_MINI) $(SOURCE_MINI) $(LIBS)

# MinGW 32-bit builds
mingw:
	i686-w64-mingw32-gcc $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

mingw-mini:
	i686-w64-mingw32-gcc $(CFLAGS) $(LDFLAGS) -o $(TARGET_MINI) $(SOURCE_MINI) $(LIBS)

# MinGW 64-bit builds
x64:
	x86_64-w64-mingw32-gcc $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

x64-mini:
	x86_64-w64-mingw32-gcc $(CFLAGS) $(LDFLAGS) -o $(TARGET_MINI) $(SOURCE_MINI) $(LIBS)

# Size comparison
size: all
	@echo "Binary sizes:"
	@ls -la *.exe 2>/dev/null || echo "No executables found"
	@echo "Byte counts:"
	@wc -c *.exe 2>/dev/null || echo "No executables found"

# Clean
clean:
	del /f *.exe 2>nul || rm -f *.exe

# Help
help:
	@echo Available targets:
	@echo   all       - Build both standard and mini versions (x64)
	@echo   $(TARGET) - Build standard version with default gcc
	@echo   $(TARGET_MINI) - Build mini version with default gcc
	@echo   mingw     - Build standard version with MinGW 32-bit
	@echo   mingw-mini- Build mini version with MinGW 32-bit
	@echo   x64       - Build standard version with MinGW 64-bit
	@echo   x64-mini  - Build mini version with MinGW 64-bit
	@echo   size      - Build all and show size comparison
	@echo   clean     - Remove built files
	@echo   help      - Show this help

.PHONY: all mingw mingw-mini x64 x64-mini size clean help