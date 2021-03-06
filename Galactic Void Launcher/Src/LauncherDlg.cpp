// LauncherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Launcher.h"
#include "LauncherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

// CLauncherDlg dialog

CLauncherDlg::CLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLauncherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CLauncherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CLauncherDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CLauncherDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CLauncherDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_CHECK1, &CLauncherDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()

// CLauncherDlg message handlers

BOOL CLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	//Open patch notes
	char* url = "http://herrybiscuit.github.io/patch%20note/";
	USES_CONVERSION;
	TCHAR* _turl = A2T(url);
	COleVariant vEmpty;
	m_browser.Navigate(_turl, &vEmpty, &vEmpty, &vEmpty, &vEmpty);

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_tabCtrl.InsertItem(0, _T("Patch Notes"));
	m_tabCtrl.InsertItem(1, _T("Options"));

	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);

	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	fstream _ifile;

	_ifile.open("launcherO.cfg", ios::in | ios::binary);
	if (_ifile.is_open())
	{
		int t;
		_ifile >> t;
		pBtn->SetCheck(t);
	}
	else
	{
		pBtn->SetCheck(0);
	}

	_ifile.close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLauncherDlg::OnPaint()
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
HCURSOR CLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLauncherDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

//play button event
void CLauncherDlg::OnBnClickedButton1()
{
	USES_CONVERSION;

	ShellExecute(GetSafeHwnd(), A2T("open"), A2T("OregonTrail Game.exe"), A2T("fromlauncher"), NULL, 1);
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	
	if (pBtn->GetCheck() == 1)
		CDialogEx::OnCancel();
}

void CLauncherDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int iSlt = m_tabCtrl.GetCurSel();
	if (iSlt == 0)
	{
		::ShowWindow(m_browser.m_hWnd, SW_HIDE);
		::ShowWindow(m_browser.m_hWnd, SW_SHOW);

		GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	}
	else if (iSlt == 1)
	{
		::ShowWindow(m_browser.m_hWnd, SW_SHOW);
		::ShowWindow(m_browser.m_hWnd, SW_HIDE);

		GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
	}
	else
	{
		::ShowWindow(m_browser.m_hWnd, SW_HIDE);
		::ShowWindow(m_browser.m_hWnd, SW_SHOW);

		GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	}

	*pResult = 0;
}

void CLauncherDlg::OnBnClickedCheck1()
{
	fstream _ifile;
	_ifile.open("launcherO.cfg", ios::out | ios::binary | ios::trunc);
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	int t = pBtn->GetCheck();
	_ifile << t;
	_ifile.close();
}
