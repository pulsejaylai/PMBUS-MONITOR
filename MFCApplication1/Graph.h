#pragma once
#include "tchart1.h"
#include "ctchart.h"
//#include "ctchart.h"
#define WM_MYUPDATEDATA7 WM_USER+107
// Graph dialog
UINT MyThreadFunction7(LPVOID pParam);
class Graph : public CDialog
{
	DECLARE_DYNAMIC(Graph)

public:
	Graph(CWnd* pParent = NULL);   // standard constructor
	virtual ~Graph();

// Dialog Data
	enum { IDD = IDD_Graph };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
afx_msg  LRESULT OnUpdateMyData7(WPARAM wParam, LPARAM lParam);
	
	
	
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	tchart1 m_vinchart;
	CTchart1 m_vinchart;
	afx_msg void OnBnClickedCancel();
};
