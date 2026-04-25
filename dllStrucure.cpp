#include <windows.h>

BOOL WINAPI DllMain(HMODULE hModule,DWORD reason, DWORD reserved){
    switch(reason){
        case DLL_PROCESS_ATTACH:
            MessageBoxW(NULL,L"You have been DLL Injected!",L"DLL Injection!",MB_OK|MB_ICONWARNING);
            break;

    }
    // IF THE DLL RUNS SUCCESSFULLY AND MANAGES TO ATTACH TO A PROCESS YOU WANT YOU HAVE TO RETURN TRUE
    return TRUE;
}