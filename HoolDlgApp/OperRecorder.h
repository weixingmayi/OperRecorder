#pragma once
#include <windows.h>

class OperRecorder
{
public:
	OperRecorder(void);
	~OperRecorder(void);

public:
	//virtual void	OnHook(int _nCode, WPARAM _wParam, LPARAM _lParam); 
	void	OnRecvMsg(const MSG& _msg);
};

