
// MassWebSwimmerDlg.h: 헤더 파일
//

#pragma once


// CMassWebSwimmerDlg 대화 상자
class CMassWebSwimmerDlg : public CDialogEx
{
	CComboBox m_typeCombo;
	CEdit m_keywordInput;
	CEdit m_amountInput;
	CString m_filePath;
	CButton m_executeButton;
	CStatic m_filePathStatic;

// 생성입니다.
public:
	CMassWebSwimmerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MASSWEBSWIMMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT, int, int);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTypeCombo();
	afx_msg void OnClickExecuteButton();
	afx_msg void OnClickFilePathButton();
	DECLARE_MESSAGE_MAP()
};
