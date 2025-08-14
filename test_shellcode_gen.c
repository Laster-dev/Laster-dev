/*
 * Test Shellcode Generator
 * Creates a simple MessageBox shellcode for testing the loader
 */

#include <windows.h>
#include <stdio.h>

// Simple test shellcode that shows a message box
// This is for testing purposes only
unsigned char test_shellcode[] = {
    // MessageBox shellcode for x86
    0x31, 0xc0,                             // xor eax, eax
    0x50,                                   // push eax (NULL)
    0x68, 0x6f, 0x78, 0x20, 0x21,         // push "ox !"
    0x68, 0x65, 0x62, 0x6f, 0x78,         // push "ebox"
    0x68, 0x73, 0x73, 0x61, 0x67,         // push "ssag"
    0x68, 0x54, 0x65, 0x73, 0x74,         // push "Test"
    0x8b, 0xcc,                             // mov ecx, esp (text)
    0x50,                                   // push eax (NULL)
    0x68, 0x73, 0x74, 0x21, 0x21,         // push "st!!"
    0x68, 0x20, 0x54, 0x65, 0x73,         // push " Tes"
    0x68, 0x6f, 0x61, 0x64, 0x65,         // push "oade"
    0x68, 0x63, 0x6f, 0x64, 0x65,         // push "code"
    0x68, 0x53, 0x68, 0x65, 0x6c,         // push "Shel"
    0x8b, 0xd4,                             // mov edx, esp (title)
    0x50,                                   // push eax (MB_OK)
    0x51,                                   // push ecx (text)
    0x52,                                   // push edx (title)
    0x50,                                   // push eax (NULL hwnd)
    0xff, 0x15                              // call [MessageBoxA]
    // Note: This is incomplete - real shellcode would need proper API resolution
};

int main() {
    FILE *f = fopen("test_shellcode.bin", "wb");
    if (f) {
        fwrite(test_shellcode, 1, sizeof(test_shellcode), f);
        fclose(f);
        printf("Test shellcode written to test_shellcode.bin (%d bytes)\n", (int)sizeof(test_shellcode));
    }
    return 0;
}