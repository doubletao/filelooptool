
// FileToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileTool.h"
#include "FileToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CString GetFilePath(CString strFullFileName)//获取文件路径
{
	CString strPath;
	strPath.Empty();

	int nPos = strFullFileName.ReverseFind(_T('\\'));
	if(nPos < 0)
		return strPath;

	strPath = strFullFileName.Left(nPos);

	return strPath;
}

static CString GetFileName(CString strFullFileName)//获取文件路径
{
	CString strName = strFullFileName;

	int nPos = strFullFileName.ReverseFind(_T('\\'));
	if(nPos > 0)
		strName = strFullFileName.Mid(nPos);
	nPos = strName.ReverseFind(_T('.'));
	if (nPos > 0)
		strName = strName.Left(nPos);

	return strName;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFileToolDlg 对话框




CFileToolDlg::CFileToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFileToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SCAN_SRC, &CFileToolDlg::OnBnClickedBtnScanSrc)
	ON_BN_CLICKED(IDC_BTN_SCAN_DES, &CFileToolDlg::OnBnClickedBtnScanDes)
	ON_BN_CLICKED(IDOK, &CFileToolDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileToolDlg 消息处理程序

BOOL CFileToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileToolDlg::OnBnClickedBtnScanSrc()
{
	CFileDialog dialog(TRUE);
	if (dialog.DoModal() == IDOK)
	{
		CString strSrcPath = dialog.GetPathName();
		GetDlgItem(IDC_EDIT_SRCPATH)->SetWindowText(strSrcPath);
	}
}


void CFileToolDlg::OnBnClickedBtnScanDes()
{
	CFileDialog dialog(FALSE);
	if (dialog.DoModal() == IDOK)
	{
		CString strDesPath = dialog.GetPathName();
		GetDlgItem(IDC_EDIT_DESPATH)->SetWindowText(strDesPath);
	}
}

#if 0
void CFileToolDlg::OnBnClickedOk()
{
	CString strSrcPath;
	GetDlgItem(IDC_EDIT_SRCPATH)->GetWindowText(strSrcPath);
	CString strDesPath;
	GetDlgItem(IDC_EDIT_DESPATH)->GetWindowText(strDesPath);
	//遍历文件夹下的文件，一个一个读到字符串里，然后写到指定文件里
	//遍历监视路径
	WIN32_FIND_DATA wfd32;
	HANDLE hFind = NULL;
	CString strMonitoringFile = GetFilePath(strSrcPath);
	strMonitoringFile += _T("\\*.*");
	hFind = ::FindFirstFile(strMonitoringFile, &wfd32);
	if(INVALID_HANDLE_VALUE != hFind)
	{
		CStdioFile fileDes;
		if (fileDes.Open(strDesPath, CFile::modeCreate | CFile::modeWrite))
		{
			do
			{
				if((wfd32.cFileName[0] == '.') || ((wfd32.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) )
					continue;
				//发现一个文件
				CString strFindName = wfd32.cFileName;
				//打开文件逐行处理，然后写入
				CStdioFile fileSrc;
				if (fileSrc.Open(GetFilePath(strSrcPath) + _T("\\") + strFindName, CFile::modeRead))
				{
					//大括号开头
					fileDes.WriteString(_T("{\n"));
					fileDes.WriteString(_T("std::string cstrShader = \n"));
					fileDes.WriteString(_T("\"\\\n"));
					CString strRead;
					while(fileSrc.ReadString(strRead))
					{
						strRead.Trim();
						if (strRead.IsEmpty())
						{
							continue;
						}
						fileDes.WriteString(strRead + _T("\\n\\\n"));
					}
					fileDes.WriteString(_T("\";\n"));
					CString strEnd;
					strFindName.MakeLower();
					strEnd.Format(_T("m_mapShaderStr[_T(\"%s\")] = cstrShader;\n"), strFindName);
					fileDes.WriteString(strEnd);
					//大括号结尾
					fileDes.WriteString(_T("}\n"));
					fileSrc.Close();
				}
			}while(::FindNextFile(hFind, &wfd32) != 0);
			FindClose(hFind);
			fileDes.Close();
		}
	}
}
#endif

void CFileToolDlg::OnBnClickedOk()
{
	CString strSrcPath;
	GetDlgItem(IDC_EDIT_SRCPATH)->GetWindowText(strSrcPath);
	CString strDesPath;
	GetDlgItem(IDC_EDIT_DESPATH)->GetWindowText(strDesPath);
	//遍历文件夹下的文件，一个一个读到字符串里，然后写到指定文件里
	//遍历监视路径
	WIN32_FIND_DATA wfd32;
	HANDLE hFind = NULL;
	CString strMonitoringFile = GetFilePath(strSrcPath);
	strMonitoringFile += _T("\\*.*");
	hFind = ::FindFirstFile(strMonitoringFile, &wfd32);
	if(INVALID_HANDLE_VALUE != hFind)
	{
		CStdioFile fileDes;
		if (fileDes.Open(strDesPath, CFile::modeCreate | CFile::modeWrite))
		{
			fileDes.WriteString(_T("[ThemeCount]\r\n"));
			fileDes.WriteString(_T("value=120\r\n"));
			int n = 0;
			do
			{
				if((wfd32.cFileName[0] == '.') || ((wfd32.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) )
					continue;
				//发现一个文件
				CString strFindName = wfd32.cFileName;
				CString strFileName = GetFileName(strFindName);
				if (strFindName.Find(_T(".ini")) > -1)
				{
					continue;
				}
				n++;
				strFileName.MakeUpper();
				//打开文件逐行处理，然后写入
				CString strSecTheme;
				strSecTheme.Format(_T("[Theme_%d]\r\n"), n);
				fileDes.WriteString(strSecTheme);

				CString strSecThemeValue;
				strSecThemeValue.Format(_T("value=%s\r\n"), strFileName);
				fileDes.WriteString(strSecThemeValue);

				CString strSecKey;
				strSecKey.Format(_T("[%s]\r\n"), strFileName);
				fileDes.WriteString(strSecKey);

				CString strSecKeyValue;
				strSecKeyValue.Format(_T("value=%s\r\n"), strFindName);
				fileDes.WriteString(strSecKeyValue);
			}while(::FindNextFile(hFind, &wfd32) != 0);
			FindClose(hFind);
			fileDes.Close();
		}
	}
}