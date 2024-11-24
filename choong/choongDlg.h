#pragma once

// CchoongDlg 대화 상자
class CchoongDlg : public CDialogEx
{
    // 생성입니다.
public:
    CchoongDlg(CWnd* pParent = nullptr); // 표준 생성자입니다.

public:
    CImage m_image; // 이미지 객체 선언
    CString m_star; // 시작 좌표
    CString m_end; // 종료 좌표
    int m_radius; //랜덤생성된 반지름

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CHOONG_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 

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
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnEnChangeEdit2();
    afx_msg void OnBnClickedBtnMake();
    void UpdateDisplay();
    void drawCircle(unsigned char* fm, int x, int y, int radius, int gray);
    bool isInCircle(int i, int j, int centerX, int centerY, int radius);
    afx_msg void OnBnClickedBtnAction();
    afx_msg void OnBnClickedBtnLoadCenter();
    void DrawCrossAndText(CClientDC& dc, int x, int y); 
};
