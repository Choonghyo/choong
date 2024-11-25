
// choongDlg.h: 헤더 파일
//

#pragma once


// CchoongDlg 대화 상자
class CchoongDlg : public CDialogEx
{
// 생성입니다.
public:
	CchoongDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOONG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDrow();
	afx_msg void OnBnClickedBtnAction();

public:
	CString m_star; // 시작 입력 좌표
	CString m_end; // 종료 좌표
	CImage m_image;
	int m_radius;   // 랜덤 반지름


	void UpdateDisplay();

	void drawCircle(unsigned char* fm, int x, int y, int radius, int gray); //원
	void moveCircle(int startX, int startY, int endX, int endY, int steps); //이동
	void CchoongDlg::DrawCrossAndText(CClientDC& dc, int x, int y, int radius);
	afx_msg void OnBnClickedBtnOpen();
};
