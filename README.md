# WIN 32 API

```cpp
// 1. OpenProcess
HANDLE hProcess = OpenProcess(
  DWORD dwDesiredAccess,   // Access rights (e.g., PROCESS_ALL_ACCESS)
  BOOL  bInheritHandle,    // Handle inheritance option
  DWORD dwProcessId        // PID of the target process
);

// 2. VirtualAllocEx
LPVOID lpBaseAddress = VirtualAllocEx(
  HANDLE hProcess,         // Handle to the target process
  LPVOID lpAddress,        // Desired starting address (NULL for auto)
  SIZE_T dwSize,           // Size of the memory region
  DWORD  flAllocationType, // Allocation type (MEM_COMMIT | MEM_RESERVE)
  DWORD  flProtect         // Memory protection (e.g., PAGE_EXECUTE_READWRITE)
);

// 3. WriteProcessMemory
BOOL bWriteStatus = WriteProcessMemory(
  HANDLE  hProcess,                // Handle to the target process
  LPVOID  lpBaseAddress,           // Address in target process
  LPCVOID lpBuffer,                // Data to be written
  SIZE_T  nSize,                   // Number of bytes
  SIZE_T  *lpNumberOfBytesWritten  // Out: bytes written
);

// 4. CreateRemoteThreadEx
HANDLE hThread = CreateRemoteThreadEx(
  HANDLE                       hProcess,
  LPSECURITY_ATTRIBUTES        lpThreadAttributes,
  SIZE_T                       dwStackSize,
  LPTHREAD_START_ROUTINE       lpStartAddress,
  LPVOID                       lpParameter,
  DWORD                        dwCreationFlags,
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  LPDWORD                      lpThreadId
);
