#pragma once
#include <windows.h>
#include <list>
using namespace std;
class HdEvent;
class OperRecorder
{
public:
	OperRecorder(void);
	~OperRecorder(void);

private:
	list<HdEvent*>	m_pEventList;
	void		Cleanup(void);
protected:
	HdEvent*	OnMouseMsg(const MSG& _msg);

public:
	HdEvent*	OnRecvMsg(const MSG& _msg);
	
};

