# read-write-mem
This C++ code demonstrates how to manipulate a process's memory by reading and writing values, specifically to change the health value of a game process. It utilizes Windows API functions to access and interact with another process's memory. Here's an explanation of the code:

### Code Breakdown:

1. **Includes**:
   - `#include <iostream>`: Used for input/output operations (e.g., printing to the console).
   - `#include <Windows.h>`: Provides Windows-specific API functions, such as `CreateToolhelp32Snapshot`, `OpenProcess`, and `WriteProcessMemory`.
   - `#include <tlhelp32.h>`: Provides functions to enumerate processes and modules on the system, like `CreateToolhelp32Snapshot` and `Module32First`.
   - `#include <tchar.h>`: Defines macros and functions for handling Unicode and ANSI strings (used for compatibility with different character sets).

2. **GetModuleBaseAddress Function**:
   - **Purpose**: This function retrieves the base address of a specific module (executable or DLL) in the process memory.
   - It takes the process ID (`pid`) and the module name (`modName`) as parameters.
   - The `CreateToolhelp32Snapshot` function creates a snapshot of the process's modules, and `Module32First` iterates through them.
   - If a module with the specified name is found, the base address of the module is returned.

3. **WriteMemory Function**:
   - **Purpose**: This function writes a given integer value to a specific memory address in the target process.
   - It uses `WriteProcessMemory` to write the data at the given address.

4. **ReadMemory Function**:
   - **Purpose**: This function reads the value of an integer from a specific memory address in the target process.
   - It uses `ReadProcessMemory` to fetch the data from the given address.

5. **Main Function**:
   - **Purpose**: This is the entry point of the program, where the memory manipulation occurs.
   - It sets the process ID (`pid`) of the target process and specifies the module (`game.exe`) whose base address is to be found.
   - `GetModuleBaseAddress` is called to find the base address of `game.exe`.
   - Once the base address is obtained, the code assumes that a health value is located at an offset (`0x123456`) from the base address.
   - The process is opened with `OpenProcess` using `PROCESS_ALL_ACCESS` permission, which allows reading and writing memory in the process.
   - `ReadMemory` is used to read the current health value, which is printed to the console.
   - `WriteMemory` sets the health value to 1 (presumably to "cheat" in the game), and a message is printed to confirm the change.
   - Finally, the process handle is closed with `CloseHandle`.

### Purpose:
- The overall purpose of this code is to demonstrate how to interact with a running process's memory in a Windows environment, which can be used for cheating in games or other memory manipulation tasks. The specific example here shows how to read and change the health value of a game process.
  
### Notes:
- The memory address offsets and process ID are hardcoded, and in a real-world scenario, these would need to be dynamically determined.
