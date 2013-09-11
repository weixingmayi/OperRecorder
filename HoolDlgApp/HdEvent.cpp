#include "StdAfx.h"
#include "HdEvent.h"
#include "HdEventString.h"

HdEvent::HdEvent(void)
{
}


HdEvent::~HdEvent(void)
{
}

void DdMouseEvent::ToString( CString& _str )
{
	LPCTSTR str = ESTR_UNHANDLEDMSG;
	switch (m_wEvent)
	{
	case WM_LBUTTONDOWN:
		str = ESTR_LBUTTONDOWN;
		break;
	case WM_LBUTTONUP:
		str = ESTR_LBUTTONUP;
		break;;
	case WM_RBUTTONDOWN:
		str = ESTR_RBUTTONDOWN;
		break;
	case WM_RBUTTONUP:
		str = ESTR_RBUTTONUP;
		break;
	default:
		break;
	}
	
	_str.Format(_T("%s %d, %d\n"), str, 
		m_pos.x, m_pos.y);
}

BOOL DdMouseEvent::ParseString( const CString& _str )
{
	return FALSE;
}

BOOL DdMouseEvent::ParseMsg( const MSG& _msg )
{
	switch (_msg.wParam)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		{
			m_wEvent = _msg.wParam;
			m_pos.x = LOWORD(_msg.lParam);
			m_pos.y = HIWORD(_msg.lParam);
		}

		return TRUE;
	default:
		break;
	}
	return FALSE;
}

BOOL DdMouseEvent::IsEventSupported( const MSG& _msg )
{
	switch (_msg.wParam)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		return TRUE;
	default:
		break;
	}
	return FALSE;
}
