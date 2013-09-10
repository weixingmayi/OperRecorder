#pragma once
#include "hookExport.h"
#include <afxwin.h>

HOOK_API LRESULT WINAPI MouseProc(int nCode,WPARAM wParam,LPARAM lParam);

HOOK_API BOOL InstallHook(DWORD _dwHandleThreadID, int _idHook, DWORD _dwHookedThreadID = 0);
HOOK_API BOOL InstallHookToWnd(HWND _hHandledWnd, int _idHook, DWORD _dwHookedThreadID = 0);

HOOK_API void UnInstallHook();