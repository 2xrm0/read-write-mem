#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h> 

uintptr_t GetModuleBaseAddress(DWORD pid, const wchar_t* modName) {
    uintptr_t baseAddress = 0;

  
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    MODULEENTRY32 modEntry;
    modEntry.dwSize = sizeof(modEntry);

   
    if (Module32First(snapshot, &modEntry)) {
        do {
           
            if (_wcsicmp(modEntry.szModule, modName) == 0) {
                baseAddress = (uintptr_t)modEntry.modBaseAddr;
                break;
            }
        } while (Module32Next(snapshot, &modEntry));
    }
    CloseHandle(snapshot);  
    return baseAddress;
}

void WriteMemory(HANDLE hProcess, uintptr_t address, int value) {
    WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), nullptr);
}

int ReadMemory(HANDLE hProcess, uintptr_t address) {
    int value = 0;
    ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(value), nullptr);
    return value;
}

int main() {
    DWORD pid = 1234; 
    const wchar_t* moduleName = L"game.exe"; 
    uintptr_t baseAddress = GetModuleBaseAddress(pid, moduleName);

    if (baseAddress == 0) {
        std::cerr << "Failed to get base address!" << std::endl;
        return 1;
    }

    uintptr_t healthAddress = baseAddress + 0x123456;

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        std::cerr << "Failed to open process" << std::endl;
        return 1;
    }

    int health = ReadMemory(hProcess, healthAddress);
    std::cout << "Current Health: " << health << std::endl;

    WriteMemory(hProcess, healthAddress, 1);
    std::cout << "Health set to 1!" << std::endl;

    CloseHandle(hProcess);
    return 0;
}
