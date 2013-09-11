#include "StdAfx.h"
#include "HookAPIFuncs.h"

extern HHOOK g_hHook;
extern HINSTANCE g_hInstance;
extern DWORD	g_dwThreadId;
extern HWND		g_hWnd;
LRESULT WINAPI MouseProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		CWnd* pWnd = AfxGetMainWnd();
		PMOUSEHOOKSTRUCT mEvent = (PMOUSEHOOKSTRUCT)lParam;
		pWnd->ScreenToClient(&(mEvent->pt));

		LPARAM pos = (LPARAM)MAKELONG(mEvent->pt.x, mEvent->pt.y);
		if (g_dwThreadId > 0)
		{
			PostThreadMessage(g_dwThreadId, WM_HOOKMOUSE_EVENT, wParam, pos);
		}
		else if(g_hWnd)
		{
			PostMessage(g_hWnd, WM_HOOKMOUSE_EVENT, wParam, pos);
		}
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
