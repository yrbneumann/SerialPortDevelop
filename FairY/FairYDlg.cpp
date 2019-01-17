
// FairYDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FairY.h"
#include "FairYDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int BaudRateArray[] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 5600, 57600, 115200 };

string ParityArray[] = { "None","Odd","Even","Mark","Space" };

string DataBitsArray[] = { "5","6","7","8" };

string StopArray[] = { "1", "1.5", "2" };

CSerialPort m_SerialPort;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CFairYDlg dialog



CFairYDlg::CFairYDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FAIRY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFairYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SELECT_COM, m_cmb_SelectCom);
	DDX_Control(pDX, IDC_CMB_BAUDRATE, m_cmb_BaudRate);
	DDX_Control(pDX, IDC_CMB_DATABITS, m_cmb_DataBits);
	DDX_Control(pDX, IDC_CMB_STOPBITS, m_cmb_StopBits);
	DDX_Control(pDX, IDC_CMB_PARITY, m_cmb_Parity);
	DDX_Control(pDX, IDC_BTN_OPEN_CLOSE, m_btn_OpenClose);
	DDX_Control(pDX, IDC_EDT_RECV, m_edt_recv);
	DDX_Control(pDX, IDC_EDT_SEND, m_edt_send);
	DDX_Control(pDX, IDC_STT_RECV_COUNT, m_stt_recvCount);
	DDX_Control(pDX, IDC_STT_SEND_COUNT, m_stt_sendCount);

	DDX_Control(pDX, IDC_CHK_EDT_RECV_COLOR, m_chk_edtRecvColor);
}

BEGIN_MESSAGE_MAP(CFairYDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_CLOSE, &CFairYDlg::OnBnClickedBtnOpenClose)
	ON_BN_CLICKED(IDC_BTN_SEND, &CFairYDlg::OnBnClickedBtnSend)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CLEAR_COUNT, &CFairYDlg::OnBnClickedBtnClearCount)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHK_EDT_RECV_COLOR, &CFairYDlg::OnBnClickedChkEdtRecvColor)
END_MESSAGE_MAP()


// CFairYDlg message handlers

BOOL CFairYDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//���ô��ڱ���
	this->SetWindowText(_T("YCOM"));

	m_stt_recvCount.SetWindowText(CString("0"));
	m_stt_recvCount.SetWindowText(CString("0"));

	CString temp;
	//��Ӳ����ʵ������б�
	for (int i = 0; i < sizeof(BaudRateArray) / sizeof(int); i++)
	{
		temp.Format(_T("%d"), BaudRateArray[i]);
		m_cmb_BaudRate.InsertString(i, temp);
	}
	temp.Format(_T("%d"), 9600);
	m_cmb_BaudRate.SetCurSel(m_cmb_BaudRate.FindString(0, temp));

	//����λ
	for (int i = 0; i < sizeof(ParityArray) / sizeof(string); i++)
	{
#ifdef UNICODE
		temp.Format(_T("%S"), ParityArray[i].c_str());
#else
		temp.Format(_T("%s"), ParityArray[i].c_str());
#endif
		m_cmb_Parity.InsertString(i, temp);
	}
	m_cmb_Parity.SetCurSel(0);

	//����λ
	for (int i = 0; i < sizeof(DataBitsArray) / sizeof(string); i++)
	{
#ifdef UNICODE
		temp.Format(_T("%S"), DataBitsArray[i].c_str());
#else
		temp.Format(_T("%s"), DataBitsArray[i].c_str());
#endif
		m_cmb_DataBits.InsertString(i, temp);
	}
	m_cmb_DataBits.SetCurSel(3);

	//ֹͣλ
	for (int i = 0; i < sizeof(StopArray) / sizeof(string); i++)
	{
#ifdef UNICODE
		temp.Format(_T("%S"), StopArray[i].c_str());
#else
		temp.Format(_T("%s"), StopArray[i].c_str());
#endif
		m_cmb_StopBits.InsertString(i, temp);
	}
	m_cmb_StopBits.SetCurSel(0);

	//��ȡ���ں�
	list<string> m_portsList = CSerialPortInfo::availablePorts();
	list<string>::iterator itor;
	TCHAR m_regKeyValue[255];
	for (itor = m_portsList.begin(); itor != m_portsList.end(); ++itor)
	{
#ifdef UNICODE
		int iLength;
		const char * _char = (*itor).c_str();
		iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, m_regKeyValue, iLength);
#else
		strcpy_s(m_regKeyValue, 255, (*itor).c_str());
#endif
		m_cmb_SelectCom.AddString(m_regKeyValue);
	}
	m_cmb_SelectCom.SetCurSel(0);

	OnBnClickedBtnOpenClose();

	m_edt_send.SetWindowText(_T("http://blog.csdn.net/itas109"));

	m_SerialPort.readReady.connect(this, &CFairYDlg::OnReceive);

	//m_comboSelectCom.AddString(_T("9600"));
	//m_comboSelectCom.AddString(_T("38400"));
	//m_comboSelectCom.AddString(_T("115200"));
	//m_comboSelectCom.SetCurSel(2);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFairYDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFairYDlg::OnPaint()
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
HCURSOR CFairYDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFairYDlg::OnBnClickedBtnOpenClose()
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_btn_OpenClose.GetWindowText(temp);//��ȡ��ť���ı�
	//UpdateData(true);
	//��ǰ��ť����Ϊ�رմ��ڣ���Ҫ�رմ���
	if (temp == _T("�رմ���"))
	{
		m_SerialPort.close();
		//���ð�ť����Ϊ���򿪴��ڡ�
		m_btn_OpenClose.SetWindowText(_T("�򿪴���"));
	}
	//��ǰ��ť����Ϊ�򿪴��ڣ�COM�ڸ�������0
	else if (m_cmb_SelectCom.GetCount() > 0)
	{
		string portName;
		int SelBaudRate;
		int SelParity;
		int SelDataBits;
		int SelStopBits;

		UpdateData(true);
		m_cmb_SelectCom.GetWindowText(temp);
#ifdef UNICODE
		portName = CW2A(temp.GetString());
#else
		portName = temp.GetBuffer();
#endif	

		m_cmb_BaudRate.GetWindowText(temp);
		SelBaudRate = _tstoi(temp);

		SelParity = m_cmb_Parity.GetCurSel();

		m_cmb_DataBits.GetWindowText(temp);
		SelDataBits = _tstoi(temp);

		SelStopBits = m_cmb_StopBits.GetCurSel();

		m_SerialPort.init(portName,
			SelBaudRate,
			itas109::Parity(SelParity),
			itas109::DataBits(SelDataBits),
			itas109::StopBits(SelStopBits)
		);

		m_SerialPort.open();

		if (m_SerialPort.isOpened())
		{
			m_btn_OpenClose.SetWindowText(_T("�رմ���"));
		}
		else
		{
			//AfxMessageBox(_T("�򿪴���ʧ��!!!,����������\r\n��ѡ����ȷ�Ĵ��ڻ�ô��ڱ�ռ��"));
		}
	}
	else
	{
		AfxMessageBox(_T("û�з��ִ��ڣ�"));
	}
}


void CFairYDlg::OnBnClickedBtnSend()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDT_SEND)->SetFocus();
	CString temp;
	UpdateData(true);
	m_btn_OpenClose.GetWindowText(temp);
	if (temp == "�򿪴���")///û�д򿪴���
	{
		AfxMessageBox(_T("�����ȴ򿪴���"));
		return;
	}

	m_edt_send.GetWindowText(temp);
	size_t len = _tcsclen(temp) + 1;;
	char* m_str = NULL;
	size_t* converted = 0;
	m_str = new char[len];
#ifdef UNICODE
	wcstombs_s(converted, m_str, len, temp.GetBuffer(0), _TRUNCATE);
#else
	m_str = temp.GetBuffer(0);
#endif

	m_SerialPort.writeData(m_str, len);

	tx += len - 1;

	CString str2;
	str2.Format(_T("%d"), tx);
	m_stt_sendCount.SetWindowText(str2);
}


void CFairYDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_SerialPort.close();
	CDialogEx::OnClose();
}

void CFairYDlg::OnReceive()
{
	char *str = new char[256];
	m_SerialPort.readAllData(str);

	CString str1(str);

	rx += str1.GetLength();

	m_edt_recv.SetSel(-1, -1);
	m_edt_recv.ReplaceSel(str1);
	m_edt_recv.LineScroll(m_edt_recv.GetLineCount());

	//Invalidate();
	////UpdateWindow();

	//CRect rect = new CRect();
	//m_edt_recv.GetClientRect(rect);
	//InvalidateRect(rect);

	CString str2;
	str2.Format(_T("%d"), rx);
	m_stt_recvCount.SetWindowText(str2);

	////����һ���ڴ��豸��������󣨼��󱸻�������  
	//CDC MemDC;
	////����һ��λͼ����  
	//CBitmap MemBitmap;
	////��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������  
	//MemDC.CreateCompatibleDC(NULL);
	////��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��  
	////���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ  
	//MemBitmap.CreateCompatibleBitmap(pDC, nWidth, nHeight);
	////��λͼѡ�뵽�ڴ��豸������  
	////ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��  
	//CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	////���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	////��Ҳ�������Լ�Ӧ���õ���ɫ  
	//MemDC.FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
	////��ͼ  
	//MemDC.MoveTo(����);
	//MemDC.LineTo(����);
	////���󱸻������е�ͼ�ο�����ǰ�˻�����  
	//pDC->BitBlt(0, 0, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);
	////��ͼ��ɺ������  
	//MemBitmap.DeleteObject();
	//MemDC.DeleteDC();

	////-------------------- -
	////	���ߣ�Larry_666
	////	��Դ��CSDN
	////	ԭ�ģ�https ://blog.csdn.net/Larry_666/article/details/77706488 
	////��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�

	//CRect rect;//���������ͼ�����С�ľ���
	//CDC *pDC;
	//CDC MemDC; //�������ݵ��ڴ�DC
	//CBitmap MemBitmap;//��������֮����ָ���ȡ��ǰ�ؼ���DC
	//pDC = GetDC();
	//GetClientRect(&rect);//��ȡ�ͻ��������С
	//
	//MemDC.CreateCompatibleDC(pDC);
	//MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//MemDC.SelectObject(&MemBitmap);//��λͼѡ���ڴ���
	//MemDC.SelectObject(&pen);
	//MemDC.FillSolidRect(rect, RGB(255, 255, 255));
	//rect1.top = rect.top;
	//rect1.left = rect.left;
	//rect1.right = rect.left + 50;
	//rect1.bottom = rect.top + 30;
	////�������½Ǿ��η�Χ
	//rect2.top = rect.bottom - 30;
	//rect2.left = rect.left;
	//rect2.right = rect.left + 50;
	//rect2.bottom = rect.bottom;
	////����������ʾ��Χ
	////
	//if (m_draw_flag)
	//{
	//	//�������Ͻǲ���
	//	MemDC.SelectStockObject(NULL_PEN);
	//	MemDC.Rectangle(rect1);
	//	MemDC.SetTextColor(RGB(0, 0, 255));
	//	MemDC.DrawText(str1, rect1, 0);

	//	//�������½ǲ���
	//	MemDC.SelectStockObject(NULL_PEN);
	//	MemDC.Rectangle(rect2);
	//	MemDC.SetTextColor(RGB(255, 0, 0));
	//	MemDC.DrawText(str2, rect2, 0);
	//}

	////�����ƶ��α�
	//CPoint start_point[5];    //�α����ʼ��
	//CBrush brush1;
	//brush1.CreateSolidBrush(RGB(255, 0, 0));
	//MemDC.SelectObject(&brush1);
	//start_point[0].x = rect.right - 15;
	//start_point[0].y = trend[0] * zoomy;
	//start_point[1].x = rect.right - 10;
	//start_point[1].y = start_point[0].y - 5;
	//start_point[2].x = rect.right;
	//start_point[2].y = start_point[0].y - 5;
	//start_point[3].x = rect.right;
	//start_point[3].y = start_point[0].y + 5;
	//start_point[4].x = rect.right - 10;
	//start_point[4].y = start_point[0].y + 5;
	//MemDC.Polygon(start_point, 5);
	////������������ͼ

	//CPen m_trendpen;   //���ƻ���
	//m_trendpen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//MemDC.SelectObject(&m_trendpen);
	//int i = 0;
	//while (i < 20)
	//{
	//	MemDC.MoveTo(rect.right - 15 - zoomx * 10 * i, zoomy*trend[i]);
	//	MemDC.LineTo(rect.right - 15 - zoomx * 10 * (i + 1), zoomy*trend[i + 1]);
	//	i++;
	//}

}

void CFairYDlg::OnBnClickedBtnClearCount()
{
	// TODO: Add your control notification handler code here
	rx = 0;
	tx = 0;
	m_stt_recvCount.SetWindowText(CString("0"));
	m_stt_sendCount.SetWindowText(CString("0"));
}


HBRUSH CFairYDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if(pWnd->GetDlgCtrlID() == IDC_EDT_RECV)
		{
			pDC->SetTextColor(RGB(0, 255, 0));//������ɫΪ��ɫ
			pDC->SetBkMode(TRANSPARENT);//�������屳��Ϊ͸����SetBkMode��SetBkColor����ͬʱʹ��
			//pDC->SetBkColor(RGB(0, 0, 255));//���屳��ɫ
			return (HBRUSH)::GetStockObject(BLACK_BRUSH);//���ؿ⻭ˢ-��-ˢ����
			//return ::CreateSolidBrush(RGB(125, 125, 255));
		}
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CFairYDlg::OnBnClickedChkEdtRecvColor()
{
	// TODO: Add your control notification handler code here
	int checkState = m_chk_edtRecvColor.GetCheck();
	if (checkState == BST_CHECKED)
	{

	}
}
