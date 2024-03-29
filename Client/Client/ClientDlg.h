
// ClientDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"


// CClientDlg 对话框
class CClientDlg : public CDialog
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CClientDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

#define  BUFFER_SIZE 1000000
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	typedef struct DATA
	{
		int length;
		char RecvBuffer[BUFFER_SIZE];
	}IMG_DATA;
	enum Type { HEART, OTHER };
	typedef struct PACKET_HEAD
	{
		Type type;
		int length;
	}HEAD;
	IMG_DATA img_data; //图像数据
	CIPAddressCtrl ip_address;//IP地址变量
	CRect m_rect; //记录对话框位置
	BOOL con_flag = FALSE; //标记按钮状态
	SOCKET ClientSocket; //声明socket
	CWinThread *plotThread = NULL; //声明线程
	static UINT PlotImageThread(LPVOID param);//声明线程函数
	CWinThread *heartThread = NULL; //声明线程
	static UINT HeartBeatThread(LPVOID param);//声明线程函数
	CRITICAL_SECTION g_cs;//临界变量
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL ConnectSocket();
	BOOL SendMsg(const char *msg);
	BOOL ReceiveImg();
	int Recv(char *recv_buf, int len);
	BOOL DrawImage();

	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();
};
