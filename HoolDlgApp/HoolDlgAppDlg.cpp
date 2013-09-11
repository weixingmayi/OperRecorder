
// HoolDlgAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HoolDlgApp.h"
#include "HoolDlgAppDlg.h"
#include "afxdialogex.h"
#include "..\hookDll2\HookAPIFuncs.h"
#include "HdEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int HookMsgHandleThread(LPVOID _lParam)
{
	CHoolDlgAppDlg* pDlg = (CHoolDlgAppDlg*)_lParam;
	MSG msg;
	HdEvent* pEvent;
	while (GetMessage(&msg, 0, 0, 0))
	{
		pEvent = pDlg->GetRecorder()->OnRecvMsg(msg);
		if(pEvent)
		{
			pDlg->OnRecorderUpdated(pEvent);
		}
	}
	return 0;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHoolDlgAppDlg dialog




CHoolDlgAppDlg::CHoolDlgAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHoolDlgAppDlg::IDD, pParent), m_bDragingPick(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHoolDlgAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG, m_EditLog);
}

BEGIN_MESSAGE_MAP(CHoolDlgAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CHoolDlgAppDlg message handlers

BOOL CHoolDlgAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_pThread = AfxBeginThread((AFX_THREADPROC(HookMsgHandleThread)),
		this, 0, CREATE_SUSPENDED, 0);
	if (m_pThread )
	{
		m_pThread->m_bAutoDelete = FALSE;
		m_pThread->ResumeThread();
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHoolDlgAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHoolDlgAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHoolDlgAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHoolDlgAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetDlgItem(IDC_STATIC_PICPICK)->GetWindowRect(&rect);
	ScreenToClient(rect);
	if (rect.PtInRect(point))
	{
		m_bDragingPick = TRUE;
		SetCapture();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CHoolDlgAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	
	CDialogEx::OnMouseMove(nFlags, point);
}


void CHoolDlgAppDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragingPick)
	{
		ReleaseCapture();
		SetRecordedWindowByPos(point);
	}
	m_bDragingPick = FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CHoolDlgAppDlg::SetRecordedWindowByPos( POINT pos )
{
	ClientToScreen(&pos);
	CWnd* pWnd = WindowFromPoint(pos);
	if (pWnd)
	{
		if(AfxMessageBox(_T("Record this window?"), MB_OKCANCEL) == IDOK)
		{
			if (m_hWnd)
			{
				StopRecord();
			}

			SetRecordedWindow(pWnd);
		}
	}
	
}

void CHoolDlgAppDlg::SetRecordedWindow( CWnd* _pWnd )
{
	m_hWnd = _pWnd->GetSafeHwnd();
	
	m_nThreadID = GetWindowThreadProcessId(m_hWnd, &m_nProcessID);

	StartRecord();
	UpdateWindowInfos();
}

void CHoolDlgAppDlg::StartRecord()
{
	if(InstallHook(m_pThread->m_nThreadID, WH_MOUSE, m_nThreadID))
	{
		m_bStarted = TRUE;
	}
	else
	{
		AfxMessageBox(_T("Start record error"));
	}
}

void CHoolDlgAppDlg::UpdateWindowInfos()
{

}

void CHoolDlgAppDlg::StopRecord()
{
	if (m_bStarted)
	{
		UnInstallHook();
		m_bStarted = FALSE;
	}
	
}

void CHoolDlgAppDlg::OnRecorderUpdated( HdEvent* _pEvent )
{
	int nF, nL;
	m_EditLog.GetSel(nF, nL);

	m_EditLog.SetSel(-1, -1);
	CString str;
	_pEvent->ToString(str);
	m_EditLog.ReplaceSel(str);

	if (nF == -1 && nL == -1)
	{
		nF = m_EditLog.GetFirstVisibleLine();
		if (nF > 0)
		{
			m_EditLog.LineScroll(-nF, 0);
		}
	}
}

