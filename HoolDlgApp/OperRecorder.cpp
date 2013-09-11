#include "StdAfx.h"
#include "OperRecorder.h"
#include "..\hookDll2\HookAPIFuncs.h"
#include <algorithm>
#include "HdEvent.h"


OperRecorder::OperRecorder(void)
{
}


OperRecorder::~OperRecorder(void)
{
	Cleanup();
}


HdEvent* OperRecorder::OnRecvMsg( const MSG& _msg )
{
	HdEvent* pRes = 0;
	switch(_msg.message)
	{
	case WM_HOOKMOUSE_EVENT:
		pRes = OnMouseMsg(_msg);
		break;
	default:
		break;
	}

	if (pRes)
	{
		m_pEventList.push_back(pRes);
	}
	return pRes;
}


HdEvent* OperRecorder::OnMouseMsg( const MSG& _msg )
{
	if (DdMouseEvent::IsEventSupported(_msg))
	{
		HdEvent* pEvent = new DdMouseEvent;
		if(!pEvent->ParseMsg(_msg))
		{
			delete pEvent;
			return NULL;
		}
		return pEvent;
	}
	return NULL;
}

void OperRecorder::Cleanup( void )
{
	for_each(m_pEventList.begin(), m_pEventList.end(),
		[](HdEvent* _p){delete _p;});
	m_pEventList.clear();
}
