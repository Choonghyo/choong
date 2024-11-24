// choongDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "choong.h"
#include "choongDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 지원입니다.

    // 구현입니다.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CchoongDlg 대화 상자

CchoongDlg::CchoongDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CHOONG_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchoongDlg::DoDataExchange(CDataExchange* pDX)
{
    //start 좌표입력
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_START, m_star);
    DDX_Text(pDX, IDC_END, m_end);
}

BEGIN_MESSAGE_MAP(CchoongDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_MAKE, &CchoongDlg::OnBnClickedBtnMake)
    ON_BN_CLICKED(IDC_BTN_ACTION, &CchoongDlg::OnBnClickedBtnAction)
END_MESSAGE_MAP()

// CchoongDlg 메시지 처리기

BOOL CchoongDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
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

    SetIcon(m_hIcon, TRUE);  
    SetIcon(m_hIcon, FALSE); 

    // 종료 좌표 초기값 설정
    m_end = _T("300,300");
    UpdateData(FALSE);
    m_radius = 0;

    return TRUE; 
}

void CchoongDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CchoongDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

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

HCURSOR CchoongDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CchoongDlg::OnBnClickedBtnMake()
{
    UpdateData(TRUE);

    // 초기화
    if (m_image.IsNull())
    {
        int nWidth = 640;
        int nHeight = 480;
        int nBpp = 8;

        m_image.Create(nWidth, -nHeight, nBpp);
        if (nBpp == 8)
        {
            static RGBQUAD rgb[256];
            for (int i = 0; i < 256; i++)
                rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
            m_image.SetColorTable(0, 256, rgb);
        }

        int nPitch = m_image.GetPitch();
        unsigned char* fm = (unsigned char*)m_image.GetBits();

        memset(fm, 0x00, nWidth * nHeight);
    }

    int startX = 0, startY = 0;
    if (_stscanf_s(m_star, _T("%d,%d"), &startX, &startY) == 2)
    {
        m_radius = rand()%100;
        unsigned char* fm = (unsigned char*)m_image.GetBits();
        drawCircle(fm, startX, startY, m_radius, 0xff);

        UpdateDisplay();
    }
    else
    {
        AfxMessageBox(_T("다시 입력 바람. 예: 50,50"));
    }
}

void CchoongDlg::OnBnClickedBtnAction()
{
    UpdateData(TRUE); // 입력된 데이터를 멤버 변수에 업데이트

    int startX = 0, startY = 0, endX = 0, endY = 0;

    // m_star
    if (_stscanf_s(m_star, _T("%d,%d"), &startX, &startY) != 2)
    {
        AfxMessageBox(_T("시작좌표오류"));
        return;
    }

    // m_end
    if (_stscanf_s(m_end, _T("%d,%d"), &endX, &endY) != 2)
    {
        AfxMessageBox(_T("종료 좌표: 300,300"));
        return;
    }

    if (m_image.IsNull())
    {
        int nWidth = 640;
        int nHeight = 480;
        int nBpp = 8;

        m_image.Create(nWidth, -nHeight, nBpp);
        if (nBpp == 8)
        {
            static RGBQUAD rgb[256];
            for (int i = 0; i < 256; i++)
                rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
            m_image.SetColorTable(0, 256, rgb);
        }

        int nPitch = m_image.GetPitch();
        unsigned char* fm = (unsigned char*)m_image.GetBits();
        memset(fm, 0x00, nWidth * nHeight);
    }

    int steps = 5; //start에서 end로 5번 나눠서 이동 
    int deltaX = (endX - startX) / steps;
    int deltaY = (endY - startY) / steps;

    TCHAR modulePath[MAX_PATH];
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    CString folderPath(modulePath);
    folderPath = folderPath.Left(folderPath.ReverseFind('\\')) + _T("\\image");

    // 폴더 생성
    if (!CreateDirectory(folderPath, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
    {
        AfxMessageBox(_T("이미지 폴더를 생성할 수 없습니다."));
        return;
    }

    unsigned char* fm = (unsigned char*)m_image.GetBits();
    int nPitch = m_image.GetPitch();

    for (int i = 0; i <= steps; ++i)
    {
        memset(fm, 0x00, m_image.GetWidth() * m_image.GetHeight());

        // 좌표 계산
        int currentX = startX + i * deltaX;
        int currentY = startY + i * deltaY;

        drawCircle(fm, currentX, currentY, m_radius, 0xff);

        UpdateDisplay();

        // 이미지 저장
        CString filePath;
        filePath.Format(_T("%s\\image_%d.bmp"), folderPath, i + 1);
        HRESULT hr = m_image.Save(filePath, Gdiplus::ImageFormatBMP);
        if (FAILED(hr))
        {
            CString errorMessage;
            errorMessage.Format(_T("이미지 저장 실패: %s"), filePath);
            AfxMessageBox(errorMessage);
            return;
        }

        // 이동 간격 딜레이
        Sleep(200);
    }
}


void CchoongDlg::UpdateDisplay()
{
    CClientDC dc(this);
    m_image.Draw(dc, 0, 0);
}

void CchoongDlg::drawCircle(unsigned char* fm, int x, int y, int radius, int gray)
{
    int nWidth = m_image.GetWidth();
    int nHeight = m_image.GetHeight();
    int nPitch = m_image.GetPitch();

    for (int j = 0; j < nHeight; ++j)
    {
        for (int i = 0; i < nWidth; ++i)
        {
            if (isInCircle(i, j, x, y, radius))
            {
                fm[j * nPitch + i] = gray;
            }
        }
    }
}

bool CchoongDlg::isInCircle(int i, int j, int centerX, int centerY, int radius)
{
    int dx = i - centerX;
    int dy = j - centerY;
    return (dx * dx + dy * dy) <= (radius * radius);
}
void CchoongDlg::OnBnClickedBtnLoadCenter()
{
    // 탐색기 창을 띄워 이미지 파일 선택
    CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
        _T("Image Files (*.bmp; *.jpg; *.jpeg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||"));

    if (dlg.DoModal() == IDOK)
    {
        CString filePath = dlg.GetPathName(); // 선택한 파일 경로

        // 기존 이미지 삭제
        if (!m_image.IsNull())
        {
            m_image.Destroy();
        }

        // 이미지 불러오기
        HRESULT hr = m_image.Load(filePath);
        if (FAILED(hr))
        {
            AfxMessageBox(_T("이미지를 불러오지 못했습니다."));
            return;
        }

        CClientDC dc(this);
        m_image.Draw(dc, 0, 0);

        // 원 중심 좌표 계산
        int centerX = m_image.GetWidth() / 2;
        int centerY = m_image.GetHeight() / 2;

        // 원 중심에 X 모양과 좌표 표시
        DrawCrossAndText(dc, centerX, centerY);
    }
}

void CchoongDlg::DrawCrossAndText(CClientDC& dc, int x, int y)
{
    // DC 설정
    CPen pen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간팬
    CPen* pOldPen = dc.SelectObject(&pen);

    // X 모양 그리기
    int size = min(m_image.GetWidth(), m_image.GetHeight()) / 20;
    dc.MoveTo(x - size, y - size);
    dc.LineTo(x + size, y + size);
    dc.MoveTo(x - size, y + size);
    dc.LineTo(x + size, y - size);

    // 텍스트 출력
    CString coords;
    coords.Format(_T("(%d, %d)"), x, y);
    if (x + size + 50 > m_image.GetWidth())
        x = x - size - 50;
    if (y - 15 < 0) // 상단 경계
        y = y + size + 15;
    dc.TextOutW(x + size + 5, y, coords); 

    // 원래 펜으로 복원
    dc.SelectObject(pOldPen);
}
