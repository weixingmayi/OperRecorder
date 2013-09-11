
// HoolDlgAppDlg.h : header file
//

#pragma once
#include "OperRecorder.h"
#include "afxwin.h"
class HdEvent;
// CHoolDlgAppDlg dialog
class CHoolDlgAppDlg : public CDialogEx
{
// Construction
public:
	CHoolDlgAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HOOLDLGAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON			m_hIcon;
	BOOL			m_bDragingPick;
	OperRecorder	m_Recorder;

	CWinThread*		m_pThread;
	BOOL			m_bStarted;

	HWND			m_hWnd;
	DWORD			m_nThreadID;
	DWORD			m_nProcessID;

	void		SetRecordedWindowByPos(POINT pos);
	void		SetRecordedWindow(CWnd* _pWnd);

	void		StartRecord();
	void		UpdateWindowInfos();
	void		StopRecord();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	OperRecorder*	GetRecorder(){return &m_Recorder;}
	void			OnRecorderUpdated(HdEvent* _pEvent);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	CEdit m_EditLog;
};
