#pragma once
class HdEvent
{
public:
	HdEvent(void);
	virtual ~HdEvent(void);

protected:
	WPARAM	m_wEvent;

public:
	virtual void ToString(CString& _str)			= 0;
	virtual BOOL ParseString(const CString& _str)	= 0;
	virtual BOOL ParseMsg(const MSG& _msg)			= 0;
};

class DdMouseEvent: public HdEvent
{
public:
	DdMouseEvent(){};
	~DdMouseEvent(){};

protected:
	CPoint		 m_pos;

public:
	virtual void	ToString(CString& _str);
	virtual BOOL	ParseString(const CString& _str);
	virtual BOOL	ParseMsg(const MSG& _msg);
	static BOOL		IsEventSupported(const MSG& _msg);
};
