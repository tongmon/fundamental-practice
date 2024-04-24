
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
}

BEGIN_MESSAGE_MAP(CMassWebSwimmerDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnSelchangeTypeCombo)
	ON_BN_CLICKED(IDC_EXECUTE_BUTTON, OnClickExecuteButton)
	ON_UPDATE_COMMAND_UI(IDC_TYPE_COMBO, OnUpdateTypeCombo)
	ON_UPDATE_COMMAND_UI(IDC_EXECUTE_BUTTON, OnUpdateExecuteButton)
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
	m_typeCombo.AddString(_T("Instagram"));
	m_typeCombo.AddString(_T("Naver"));
	m_typeCombo.AddString(_T("Google"));

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
}

void CMassWebSwimmerDlg::OnUpdateExecuteButton(CCmdUI* pUI)
{
	if (m_filePath.IsEmpty())
	{
		pUI->Enable(FALSE);
		return;
	}

	CString keyword;
	m_keywordInput.GetWindowText(keyword);

	if (keyword.IsEmpty())
	{
		pUI->Enable(FALSE);
		return;
	}

	CString amount;
	m_amountInput.GetWindowText(amount);

	if (amount.IsEmpty())
	{
		pUI->Enable(FALSE);
		return;
	}

	pUI->Enable(TRUE);
}

void CMassWebSwimmerDlg::OnUpdateTypeCombo(CCmdUI* pUI)
{
	// 비활성화
	// pUI->Enable(FALSE);
}