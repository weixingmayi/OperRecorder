#include "StdAfx.h"
#include "HookAPIFuncs.h"

extern HHOOK g_hHook;
extern HINSTANCE g_hInstance;
extern DWORD	g_dwThreadId;
extern HWND		g_hWnd;
LRESULT WINAPI MouseProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if (g_dwThreadId > 0)
	{
		PostThreadMessage(g_dwThreadId, nCode, wParam, lParam);
	}
	else if(g_hWnd)
	{
		PostMessage(g_hWnd, nCode, wParam, lParam);
	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

BOOL InstallHook(DWORD _dwHandleThreadID, int _idHook, DWORD _dwHookedThreadID)
{
	g_hHook = SetWindowsHookEx(_idHook, MouseProc, g_hInstance, _dwHookedThreadID);
	g_dwThreadId = _dwHandleThreadID;
	return g_hHook != NULL;
}

void UnInstallHook()
{
	UnhookWindowsHookEx(g_hHook);
}

HOOK_API BOOL InstallHookToWnd( HWND _hHandledWnd, int _idHook, DWORD _dwHookedThreadID /*= 0*/ )
{
	g_hHook = SetWindowsHookEx(_idHook, MouseProc, g_hInstance, _dwHookedThreadID);
	g_hWnd = _hHandledWnd;
	return g_hHook != NULL;
}
