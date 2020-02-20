
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MyListctrl.h"


UINT MyThreadFunction(LPVOID pParam);
UINT MyThreadFunction1(LPVOID pParam);
UINT MyThreadFunction8(LPVOID pParam);
#define WM_MYUPDATEDATA WM_USER+100
#define WM_MYUPDATEDATA1 WM_USER+101
#define WM_MYUPDATEDATA2 WM_USER+102
#define WM_MYUPDATEDATA3 WM_USER+103
#define WM_MYUPDATEDATA4 WM_USER+104
#define WM_MYUPDATEDATA5 WM_USER+105
#define WM_MYUPDATEDATA6 WM_USER+106
#define WM_MYUPDATEDATA8 WM_USER+108
// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg  LRESULT OnUpdateMyData(WPARAM wParam, LPARAM lParam);
	afx_msg  LRESULT OnUpdateMyData1(WPARAM wParam, LPARAM lParam);
	afx_msg  LRESULT OnUpdateMyData2(WPARAM wParam, LPARAM lParam);
	afx_msg  LRESULT OnUpdateMyData3(WPARAM wParam, LPARAM lParam);
	afx_msg  LRESULT OnUpdateMyData4(WPARAM wParam, LPARAM lParam);
	afx_msg  LRESULT OnUpdateMyData6(WPARAM wParam, LPARAM lParam);
	afx_msg  LRESULT OnUpdateMyData8(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
CStatusBarCtrl m_StatusBar;



	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	MyListctrl m_list1;
	afx_msg void OnFileOpen32771();
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStop();
	afx_msg CString GetInpCurr();
	afx_msg CString GetInpVin();
	CStatic m_ivuv;
	CStatic m_ocp;
	CStatic m_ovp;
	CStatic m_pot;
	CStatic m_sot;
	CStatic m_normal;
	afx_msg void OnClickedCheckhpe();
	afx_msg void OnClickedChecklenovo();
	//afx_msg void OnBnClickedPause();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnIddGraph();
	afx_msg void OnChart();
	afx_msg void OnBnClickedDemo();
	afx_msg void OnBnClickedDemo2();
};
