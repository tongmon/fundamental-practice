
// MassWebSwimmerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MassWebSwimmer.h"
#include "MassWebSwimmerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMassWebSwimmerDlg 대화 상자



CMassWebSwimmerDlg::CMassWebSwimmerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MASSWEBSWIMMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMassWebSwimmerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_typeCombo);
	DDX_Control(pDX, IDC_KEYWORD_INPUT, m_keywordInput);
	DDX_Control(pDX, IDC_AMOUNT_INPUT, m_amountInput);
	DDX_Control(pDX, IDC_EXECUTE_BUTTON, m_executeButton);
	DDX_Control(pDX, IDC_FILEPATH_STATIC, m_filePathStatic);
}

BEGIN_MESSAGE_MAP(CMassWebSwimmerDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnSelchangeTypeCombo)
	ON_BN_CLICKED(IDC_FILEPATH_BUTTON, OnClickFilePathButton)
	ON_BN_CLICKED(IDC_EXECUTE_BUTTON, OnClickExecuteButton)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

BOOL CMassWebSwimmerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyle(0, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, TRUE);

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

#pragma region Init Controls
	m_typeCombo.InsertString(-1, _T("Instagram"));
	m_typeCombo.InsertString(-1, _T("Naver"));
	m_typeCombo.InsertString(-1, _T("Google"));
	m_typeCombo.SetCurSel(0);

	CString placeholderText = _T("Please input your keyword here.");
	::SendMessage(m_keywordInput.GetSafeHwnd(), EM_SETCUEBANNER, TRUE, reinterpret_cast<LPARAM>(placeholderText.GetString()));

	placeholderText = _T("Please input your maximum search amount here.");
	::SendMessage(m_amountInput.GetSafeHwnd(), EM_SETCUEBANNER, TRUE, reinterpret_cast<LPARAM>(placeholderText.GetString()));
#pragma endregion


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

LRESULT CMassWebSwimmerDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
#pragma region Process Execute Button Enabling
	BOOL bSelectEnable = TRUE;

	if (m_filePath.IsEmpty())
		bSelectEnable = FALSE;

	if (bSelectEnable)
	{
		CString keyword;
		m_keywordInput.GetWindowText(keyword);

		if (keyword.IsEmpty())
			bSelectEnable = FALSE;
	}

	if (bSelectEnable)
	{
		CString amount;
		m_amountInput.GetWindowText(amount);

		if (amount.IsEmpty())
			bSelectEnable = FALSE;
	}

	m_executeButton.EnableWindow(bSelectEnable);
#pragma endregion

	return 0;
}

void CMassWebSwimmerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CMassWebSwimmerDlg::OnClose()
{
	CDialogEx::OnClose();
}

BOOL CMassWebSwimmerDlg::PreTranslateMessage(MSG* pMsg)
{
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMassWebSwimmerDlg::OnSize(UINT nType, int cx, int cy)
{
	// CWnd* pwndParent = this->GetParent();
	// 
	// CRect rc;
	// pwndParent->GetWindowRect(&rc);

	CDialogEx::OnSize(nType, cx, cy);
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMassWebSwimmerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMassWebSwimmerDlg::OnSelchangeTypeCombo()
{

}

void CMassWebSwimmerDlg::OnClickExecuteButton()
{
}

void CMassWebSwimmerDlg::OnClickFilePathButton()
{
	CFolderPickerDialog folderPickerDlg(NULL, OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);
	if (folderPickerDlg.DoModal() == IDOK)
	{
		m_filePath = folderPickerDlg.GetFolderPath();
		m_filePathStatic.SetWindowText(m_filePath);
	}

	// CString filter, initDir;
	// size_t pathCnt = 1, size = pathCnt * MAX_PATH;
	// auto fileName = std::make_unique<TCHAR[]>(size);
	// fileName[0] = 0;
	// 
	// OPENFILENAME ofn;
	// std::memset(&ofn, 0, sizeof(OPENFILENAME));
	// ofn.lStructSize = sizeof(OPENFILENAME);
	// ofn.hwndOwner = this->GetSafeHwnd();
	// ofn.lpstrFilter = filter.GetString();
	// ofn.lpstrFile = fileName.get();
	// ofn.lpstrTitle = _T("Select file path");
	// ofn.nMaxFile = size;
	// ofn.lpstrInitialDir = initDir.GetString();
	// ofn.Flags = OFN_EXPLORER | (pathCnt == 1 ? 0 : OFN_ALLOWMULTISELECT);
	// 
	// if (GetOpenFileName(&ofn))
	// {
	// 	if (pathCnt == 1)
	// 		m_filePath = ofn.lpstrFile;
	// 	else
	// 	{
	// 		TCHAR* filePt = ofn.lpstrFile;
	// 		CString targetDir = filePt;
	// 		filePt += (targetDir.GetLength() + 1);
	// 
	// 		while (*filePt)
	// 		{
	// 			CString targetFile = filePt;
	// 			filePt += (targetFile.GetLength() + 1);
	// 			m_filePath = m_filePath + _T(";") + targetDir + _T("\\") + targetFile;
	// 		}
	// 	}
	// }
}