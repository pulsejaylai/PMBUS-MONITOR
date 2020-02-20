// Graph.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Graph.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"
#include "tchart1.h"
#include "CAxes.h"
#include "CAxis.h"
#include "CLegend.h"
#include "CSeries.h"
// Graph dialog
int xvalue=0;
CWinThread* MyThread7;
int start=0;



IMPLEMENT_DYNAMIC(Graph, CDialog)

Graph::Graph(CWnd* pParent /*=NULL*/)
	: CDialog(Graph::IDD, pParent)
{

}

Graph::~Graph()
{
}

void Graph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_VinChart, m_vinchart);
	DDX_Control(pDX, IDC_VinChart, m_vinchart);
}


BEGIN_MESSAGE_MAP(Graph, CDialog)
	ON_BN_CLICKED(IDOK, &Graph::OnBnClickedOk)
ON_MESSAGE(WM_MYUPDATEDATA7,OnUpdateMyData7)
ON_BN_CLICKED(IDCANCEL, &Graph::OnBnClickedCancel)
END_MESSAGE_MAP()


// Graph message handlers


void Graph::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)AfxGetMainWnd();  
	//pDlg->SendMessage(WM_MYUPDATEDATA6,NULL,NULL);
	start=1;
	MyThread7=AfxBeginThread(MyThreadFunction7,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
	/*HWND hWnd1;
	HWND buttonhWnd;
	hWnd1=::FindWindow(NULL,_T("PMBUS"));	
	buttonhWnd=::GetDlgItem(hWnd1,IDOK);
	 
	 ::SendMessage(buttonhWnd, BM_CLICK, 0, 0);  */
	//::SendMessage(hWnd1,WM_SHOWWINDOW,SW_HIDE,SW_PARENTCLOSING);
	//CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)GetParent();
	//pDlg->demo;
	//pDlg->
	/*CMFCApplication1Dlg dlg;
	CString vin;
	//vin=dlg.GetInpVin();
	AfxMessageBox(dlg.GetInpVin());*/
	//CDialog::OnOK();
}
UINT MyThreadFunction7( LPVOID pParam )
{

//do
//{
CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)AfxGetMainWnd();  
	pDlg->SendMessage(WM_MYUPDATEDATA6,NULL,NULL);

//}while(start==1);



return 0;
}



LRESULT Graph::OnUpdateMyData7(WPARAM wParam, LPARAM lParam)
{
char *str22= (char*)wParam;	
float vinreading;
CSeries lineSeries = (CSeries)m_vinchart.Series(0);	
	//AfxMessageBox(CString(str22));
vinreading=atof(str22);
lineSeries.AddXY(xvalue,vinreading+1,NULL,RGB(255,0,255)); 
xvalue=xvalue+1;

return 0;
}

void Graph::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//start=0;
	HWND buttonhWnd;
	HWND hWnd1;
	hWnd1=::FindWindow(NULL,_T("PMBUS"));	
	buttonhWnd=::GetDlgItem(hWnd1,IDC_Demo2);
	 
	 ::SendMessage(buttonhWnd, BM_CLICK, 0, 0);
	CDialog::OnCancel();
}
