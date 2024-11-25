
// choongDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "choong.h"
#include "choongDlg.h"
#include "afxdialogex.h"
#include <afxdlgs.h>

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

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
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_START, m_star);
	DDX_Text(pDX, IDC_END, m_end);
}

BEGIN_MESSAGE_MAP(CchoongDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DROW, &CchoongDlg::OnBnClickedBtnDrow)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CchoongDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CchoongDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CchoongDlg 메시지 처리기

BOOL CchoongDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CchoongDlg::OnPaint()
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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CchoongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchoongDlg::OnBnClickedBtnDrow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//Drow (IDC_BTN_DROW)버튼

	UpdateData(TRUE);

	int startX = 0;
	int startY = 0;

	if (_stscanf_s(m_star, _T("%d,%d"), &startX, &startY) == 2)
	{
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

			unsigned char* fm = (unsigned char*)m_image.GetBits();
			memset(fm, 0x00, nWidth * nHeight);
		} 
		m_radius = rand() % 100;

		unsigned char* fm = (unsigned char*)m_image.GetBits();
		drawCircle(fm, startX, startY, m_radius, 0xff);

		UpdateDisplay();
	}
	else {
		AfxMessageBox(_T("다시입력 바람. (예: 50,50)"));
	}
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
			int dx = i - x;
			int dy = j - y;
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				fm[j * nPitch + i] = gray;
			}
		}
	}
}
void CchoongDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CchoongDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//Action(IDC_BTN_ACTION)  버튼

	UpdateData(TRUE);

	int startX = 0, startY = 0;
	int endX = 0, endY = 0;

	if (_stscanf_s(m_star, _T("%d,%d"), &startX, &startY) != 2)
	{
		AfxMessageBox(_T("시작좌표 확인."));
		return;
	}
	if (_stscanf_s(m_end, _T("%d,%d"), &endX, &endY) != 2)
	{
		AfxMessageBox(_T("다시입력 바람. (예: 300, 300)"));
		return;
	}
	moveCircle(startX, startY, endX, endY, 5);//종료까지 5번 이동하여 각이미지 저장.
}


void CchoongDlg::moveCircle(int startX, int startY, int endX, int endY, int steps)
{

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

		unsigned char* fm = (unsigned char*)m_image.GetBits();
		memset(fm, 0x00, nWidth * nHeight);
	}
	int deltaX = (endX - startX) / steps;
	int deltaY = (endY - startY) / steps;

	//상대경로이용하여 이미지 폴더 생성후 저장
	//현재 시점에서 경로(C:\projects\mfcStudy\choong\x64\Debug) 여기임
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	PathRemoveFileSpec(modulePath);
	SetCurrentDirectory(modulePath);
	CString folderPath = _T(".\\image"); 

	// 폴더 생성
	if (!CreateDirectory(folderPath, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("이미지 폴더 생성 실패."));
		return;
	}

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();

	for (int i = 0;i <= steps;i++)
	{
		memset(fm, 0x00, m_image.GetWidth() * m_image.GetHeight());

		int currentX = startX + i * deltaX;
		int currentY = startY + i * deltaY;

		drawCircle(fm, currentX, currentY, m_radius, 0xff);
		UpdateDisplay();

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

		Sleep(200);
	}
}

void CchoongDlg::OnBnClickedBtnOpen()
{
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Image Files (*.bmp; *.jpg; *.jpeg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName(); 

		if (!m_image.IsNull())
		{
			m_image.Destroy();
		}

		HRESULT hr = m_image.Load(filePath);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("불러오기 실패."));
			return;
		}

		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);

		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();
		int nPitch = m_image.GetPitch();
		unsigned char* pBits = (unsigned char*)m_image.GetBits();

		int sumX = 0, sumY = 0, count = 0;
		for (int y = 0; y < nHeight; y++)
		{
			for (int x = 0; x < nWidth; x++)
			{
				if (pBits[y * nPitch + x] == 0xFF)
				{
					sumX += x;
					sumY += y;
					count++;
				}
			}
		}

		if (count > 0)
		{
			int centerX = sumX / count; 
			int centerY = sumY / count; 

			DrawCrossAndText(dc, centerX, centerY, m_radius);
		}
		else
		{
			AfxMessageBox(_T("이미지에서 원의 중심을 찾을 수 없습니다."));
		}
	}
}

void CchoongDlg::DrawCrossAndText(CClientDC& dc, int x, int y, int radius)
{
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간
	CPen* pOldPen = dc.SelectObject(&pen);

	int size = 5;
	dc.MoveTo(x - size, y - size);
	dc.LineTo(x + size, y + size);
	dc.MoveTo(x - size, y + size);
	dc.LineTo(x + size, y - size);

	CString coords;
	coords.Format(_T("(%d, %d), Radius: %d"), x, y, radius);
	dc.TextOutW(x + size + 5, y, coords); 

	dc.SelectObject(pOldPen);
}
