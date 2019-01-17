
// FairYDlg.h : header file
//

#pragma once
#include "SerialPort.h"
#include "SerialPortInfo.h"
#include "afxwin.h"

using namespace std;
using namespace itas109;

extern CSerialPort m_SerialPort;

// CFairYDlg dialog
class CFairYDlg : public CDialogEx, public has_slots<>
{
// Construction
public:
	CFairYDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAIRY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void OnSendMessage(unsigned char *str, int port, int str_len);
	void OnReceive();


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmb_SelectCom;
	CComboBox m_cmb_BaudRate;
	CComboBox m_cmb_DataBits;
	CComboBox m_cmb_StopBits;
	CComboBox m_cmb_Parity;
	CButton m_btn_OpenClose;
	CEdit m_edt_recv;
	CEdit m_edt_send;
	CStatic m_stt_recvCount;
	CStatic m_stt_sendCount;
	afx_msg void OnBnClickedBtnOpenClose();
	afx_msg void OnBnClickedBtnSend();
private:
	int rx;
	int tx;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnClearCount();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_chk_edtRecvColor;
	afx_msg void OnBnClickedChkEdtRecvColor();
};
