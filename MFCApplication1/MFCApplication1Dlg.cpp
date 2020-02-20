
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "WinI2CUSBpro.h"
#include "Source.h"
#include "MyListctrl.h"
#include "Graph.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
int NumberOfDevices,i2cdebug,duma,tx,tt,hang,lie,xzhuan=0,pmbus1,pmbus2,start2=0;
int SerialNumbers[8],addressq,subaddressno,namelength,prilength,seclength,vinno;
unsigned char Address[4],ErrorCode,subaddress[50],modelname,priaddress,secaddress;
CWinThread* MyThread;
CWinThread* MyThread8;
//string HexToBin(const string &strHex);
//string s;
CString filename,au[50],zutai,zutais[20],zhx[256],VINREAD;
 HICON m_hIcon_close;
HICON m_hIcon_open;
void func_binary(unsigned int n);
int ledpan;
HANDLE hmutex;
















class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChart();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CHART, &CAboutDlg::OnChart)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_IVUVP, m_ivuv);
	DDX_Control(pDX, IDC_OCP, m_ocp);
	DDX_Control(pDX, IDC_OVP, m_ovp);
	DDX_Control(pDX, IDC_POT, m_pot);
	DDX_Control(pDX, IDC_SOT, m_sot);
	DDX_Control(pDX, IDC_Normal, m_normal);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_MESSAGE(WM_MYUPDATEDATA,OnUpdateMyData)
	ON_MESSAGE(WM_MYUPDATEDATA1,OnUpdateMyData1)
	ON_MESSAGE(WM_MYUPDATEDATA2,OnUpdateMyData2)
	ON_MESSAGE(WM_MYUPDATEDATA3,OnUpdateMyData3)
	ON_MESSAGE(WM_MYUPDATEDATA4,OnUpdateMyData4)
	ON_MESSAGE(WM_MYUPDATEDATA6,OnUpdateMyData6)
	ON_MESSAGE(WM_MYUPDATEDATA8,OnUpdateMyData8)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_OPEN32771, &CMFCApplication1Dlg::OnFileOpen32771)
	ON_BN_CLICKED(ID_Begin, &CMFCApplication1Dlg::OnBnClickedBegin)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_Stop, &CMFCApplication1Dlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_CHECKHPE, &CMFCApplication1Dlg::OnClickedCheckhpe)
	ON_BN_CLICKED(IDC_CHECKLenovo, &CMFCApplication1Dlg::OnClickedChecklenovo)
	//ON_BN_CLICKED(ID_PAUSE, &CMFCApplication1Dlg::OnBnClickedPause)
	ON_WM_CTLCOLOR()
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CMFCApplication1Dlg::OnCustomdrawList1)
//	ON_COMMAND(IDD_Graph, &CMFCApplication1Dlg::OnIddGraph)
ON_COMMAND(ID_CHART, &CMFCApplication1Dlg::OnChart)
ON_BN_CLICKED(IDC_Demo, &CMFCApplication1Dlg::OnBnClickedDemo)
ON_BN_CLICKED(IDC_Demo2, &CMFCApplication1Dlg::OnBnClickedDemo2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int i,ze;
CString dd,dd2,dd3,zs;
CString snumber;//="USB Card SerialNumber:";
char * userc1;
	  char *pnext=NULL;
	char *p2;
LPCTSTR pp1;
	HWND buttonhWnd,buttonhWnd1,buttonhWnd3,buttonhWnd4;
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
/*SYSTEMTIME t;
char t_y[256];

GetLocalTime(&t);//调用获取系统时间api

sprintf_s(t_y,"%04d_%02d_%02d_%02d_%02d_%02d_%3d",t.wYear,t.wMonth,t.wDay,t.wHour,
     t.wMinute,t.wSecond,t.wMilliseconds);  
AfxMessageBox(CString(t_y));*/
/*SYSTEMTIME t;
char t_y[256],t_y2[256],t_y3[256];
GetLocalTime(&t);//调用获取系统时间api
if(t.wMilliseconds<10)
{
strcpy_s(t_y3,"00");
sprintf_s(t_y2,"%d",t.wMilliseconds);
strcat_s(t_y3,t_y2);
}
if((t.wMilliseconds>=10)&&(t.wMilliseconds<100))	
{
strcpy_s(t_y3,"0");
sprintf_s(t_y2,"%d",t.wMilliseconds);
strcat_s(t_y3,t_y2);
}
if(t.wMilliseconds>=100)	
{
sprintf_s(t_y3,"%d",t.wMilliseconds);
}
	sprintf_s(t_y,"%04d%02d%02d%02d%02d%02d",t.wYear,t.wMonth,t.wDay,t.wHour,
     t.wMinute,t.wSecond);  
strcat_s(t_y,t_y3);
	AfxMessageBox(CString(t_y));*/




	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	snumber="USB Card SerialNumber:";
	// TODO: Add extra initialization here
	 buttonhWnd=::GetDlgItem(m_hWnd,IDOK);
	 
	 ::SendMessage(buttonhWnd, BM_CLICK, 0, 0);  
	//usb_init();
	m_StatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, CRect(0,0,0,0), this, 0);

               int strPartDim[4]= {300,400,500,500}; //分割数量
               m_StatusBar.SetParts(4, strPartDim);

               //设置状态栏文本
              if(NumberOfDevices==0)
			  {
				  m_StatusBar.SetText(_T("No USB I2C Card"), 0, 0);
			  }
			 if(NumberOfDevices>0) 
			 {
               for(i=0;i<NumberOfDevices;i++)
	          {
		dd.Format(_T("%6d"),SerialNumbers[i]);
	     
		dd2=" ";	
         dd3=dd3+dd+dd2;	
          }

			  /* pp1=dd3.GetBuffer(0);
	dd3.ReleaseBuffer();
	userc1 = new char [dd3.GetLength()+1]; 
	strcpy_s(userc1,dd3.GetLength()+1,CT2CA(pp1));	  
	AfxMessageBox(CString(userc1));	*/	 
	snumber=snumber+dd3;
	m_StatusBar.SetText(LPCTSTR(snumber),0,0);
			
			 }
		
			 
	
			
			 
			 
			 
			 m_StatusBar.SetText(_T("Ready"), 1, 0);
               CTime Time;
 
    Time = CTime::GetCurrentTime();
 
   // m_StatusBar.SetPaneText(3,Time.Format("%H:%M:%S"));
  m_StatusBar.SetText(Time.Format("%H:%M:%S"),2,0);
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	 SetTimer(1,1000,NULL);
	 m_StatusBar.SetText(_T("Wait"), 3, 0);
	
/*LONG lStyle;
      lStyle = GetWindowLong(m_list1.m_hWnd, GWL_STYLE);//获取当前窗口style
      lStyle &= ~LVS_TYPEMASK; //清除显示方式位
      lStyle |= LVS_REPORT; //设置style
      SetWindowLong(m_list1.m_hWnd, GWL_STYLE, lStyle);//设置style
 
      DWORD dwStyle = m_list1.GetExtendedStyle();
      dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
      dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
      //dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
       dwStyle |= LVS_SHOWSELALWAYS;//item前生成checkbox控件
	 dwStyle |= LVS_EX_DOUBLEBUFFER;
	   m_list1.SetExtendedStyle(dwStyle); //设置扩展风格	
	 m_list1.InsertColumn(0,_T("Address"));//添加列 
	  m_list1.InsertColumn(1,_T("02"));//添加列   
m_list1.InsertColumn(2,_T("30"));  
m_list1.InsertColumn(3,_T("01"));	
m_list1.InsertColumn(4,_T("40"));
m_list1.InsertColumn(5,_T("42"));
m_list1.InsertColumn(6,_T("44"));
m_list1.InsertColumn(7,_T("46"));
m_list1.InsertColumn(8,_T("48"));
m_list1.InsertColumn(9,_T("10"));  
m_list1.InsertColumn(10,_T("11"));	
m_list1.InsertColumn(11,_T("12"));
m_list1.InsertColumn(12,_T("20"));
m_list1.InsertColumn(13,_T("21"));
m_list1.InsertColumn(14,_T("22"));
m_list1.InsertColumn(15,_T("22"));



m_list1.SetColumnWidth(0, 80);
m_list1.SetColumnWidth(1, 50);//设置列宽   
m_list1.SetColumnWidth(2, 50);  
m_list1.SetColumnWidth(3, 50);//设置列宽	
m_list1.SetColumnWidth(4, 50);//设置列宽   
m_list1.SetColumnWidth(5, 50);  
m_list1.SetColumnWidth(6, 50);//设置列宽	
m_list1.SetColumnWidth(7, 50);//设置列宽			
m_list1.SetColumnWidth(8, 50);//设置列宽		
m_list1.SetColumnWidth(9, 50);//设
m_list1.SetColumnWidth(10, 50);//设置列宽   
m_list1.SetColumnWidth(11, 50);  
m_list1.SetColumnWidth(12, 50);//设置列宽	
m_list1.SetColumnWidth(13, 50);//设置列宽			
m_list1.SetColumnWidth(14, 50);//设置列宽		
m_list1.SetColumnWidth(15, 50);*/
//m_list1.SetColumnWidth(15, 50);
/*m_list1.InsertItem(0,_T("D0"));
m_list1.InsertItem(1,_T("D2"));
m_list1.InsertItem(2,_T("D4"));
m_list1.InsertItem(3,_T("D6"));	*/
m_hIcon_open=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2 ));
m_hIcon_close=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1 ));	
//m_list1.SetColor(0, 1, RGB(255,255,255));
/*CStatic *pStatic=(CStatic*)GetDlgItem(IDC_IVUVP);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_open);  	
CStatic *pStatic1=(CStatic*)GetDlgItem(IDC_OVP);   
	pStatic1-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic1-> SetIcon(m_hIcon_open);	
CStatic *pStatic2=(CStatic*)GetDlgItem(IDC_OCP);   
	pStatic2-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic2-> SetIcon(m_hIcon_open);	
CStatic *pStatic3=(CStatic*)GetDlgItem(IDC_POT);   
	pStatic3-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic3-> SetIcon(m_hIcon_open);	
CStatic *pStatic4=(CStatic*)GetDlgItem(IDC_SOT);   
	pStatic4-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic4-> SetIcon(m_hIcon_open);	
CStatic *pStatic5=(CStatic*)GetDlgItem(IDC_Normal);   
	pStatic5-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic5-> SetIcon(m_hIcon_open);	
((CButton*)GetDlgItem(IDC_CHECKHPE))->SetCheck(TRUE);
*/
CStatic *pStatic6=(CStatic*)GetDlgItem(IDC_IVSTATUE);   
	pStatic6-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic6-> SetIcon(m_hIcon_open);  	
CStatic *pStatic7=(CStatic*)GetDlgItem(IDC_OVSTATUE);   
	pStatic7-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic7-> SetIcon(m_hIcon_open);	
CStatic *pStatic8=(CStatic*)GetDlgItem(IDC_TemSTATUE);   
	pStatic8-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic8-> SetIcon(m_hIcon_open);	
CStatic *pStatic9=(CStatic*)GetDlgItem(IDC_FanSTATUE);   
	pStatic9-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic9-> SetIcon(m_hIcon_open);	
CStatic *pStatic10=(CStatic*)GetDlgItem(IDC_OVFAULT);   
	pStatic10-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic10-> SetIcon(m_hIcon_open);
CStatic *pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_VMAXWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_VONMAXWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_VOFFMAXWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_VTRACKERR);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
//pStatic9-> SetIcon(m_hIcon_open);	
pStatic11=(CStatic*)GetDlgItem(IDC_OVFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_OFF);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_INOPWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);

pStatic11=(CStatic*)GetDlgItem(IDC_OCFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OCLV);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OCWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UCFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_CSFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_PLMODE);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OPFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OPWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);

pStatic11=(CStatic*)GetDlgItem(IDC_OTFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OTWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UTWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UTFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_NA);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_NA2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_NA3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_NA4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);

pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);

pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);

//ze=DEC(_T("037F"));
//ze=StrToNumber16("70");
//char buffshi[256];
//sprintf_s(buffshi, "%d",ze);
//AfxMessageBox(CString(buffshi));
/*zs=DECToBIN(28);
//zs=zs.GetAt(0);
AfxMessageBox(zs);
int lx;
CString ff[17];
//char buffshi[256];
//sprintf_s(buffshi, "%d",zs.GetLength());
//AfxMessageBox(CString(buffshi));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zs.GetLength()-1))
	{
		ff[lx]=zs.GetAt(zs.GetLength()-1-lx);
		//AfxMessageBox(zs.GetAt(zs.GetLength()-1-lx));
	}
if(lx>(zs.GetLength()-1))
{
ff[lx]="0";
}
AfxMessageBox(ff[lx]);
}
*/







CFont *m_font4;
m_font4=new CFont;	
m_font4->CreateFont(45,30,0,0,700,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS, _T("Calibri"));  
//m_font.CreatePointFont(800,"Ш砰");
GetDlgItem(IDC_PStatue)->SetFont(m_font4);		
GetDlgItem(IDC_PStatue)->SetWindowText(_T("Wait"));	
//GetDlgItem(IDC_PStatue)->ShowWindow(SW_HIDE);		
CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKHPE);
pBtn->SetCheck(1);
return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox(_T("33"));
	//delay(1000);
	NumberOfDevices=GetSerialNumbers((int *) SerialNumbers);
	

	
	//	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CTime Time;
 Time = CTime::GetCurrentTime();
//m_StatusBar.SetPaneText(3,Time.Format("%H:%M:%S"));
  m_StatusBar.SetText(Time.Format("%H:%M:%S"), 2, 0);
//m_StatusBar.setpan
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication1Dlg::OnFileOpen32771()
{
	// TODO: Add your command handler code here
CString strFilter,strFilePath,strFilePath1,address,addresszu[4];
 int nitemcount;
 char * userc1;
	  char *pnext=NULL;
	char *p2;
char str4[256],relaydebugs[256]; 
char bufx[256],bufx1[256];

LPCTSTR pp1;
int i,relaydebug,ii,jj,u,v,z,z2,xm;
CString currs,volts,relays,vspecmaxs,vspecmins,Dvmaxs,Dactype,Dnum,debbug,Dvmins,Ddctype,loadnos,loadadds,loadshuns,tempt;	
CString testnos,agilent_adds,shuntvs,shuntis,acadds,dcadds,relayadds,channels,fs,ds,i2cma,model,subaddresszu[50];
strFilter.Format(_T("Ini Files (*ini)|*ini||"));
	CFileDialog dlg(TRUE, NULL,_T(""), NULL, strFilter);
if(dlg.DoModal()==IDOK)
{
	strFilePath=dlg.GetPathName();	
strFilePath1=strFilePath;
	
 GetPrivateProfileString(_T("Info"),_T("Model"),_T("1"),model.GetBuffer(256),256,strFilePath);
model.ReleaseBuffer(256);
if(model=="1")
{
 pmbus1=1;
	((CButton*)GetDlgItem(IDC_CHECKLenovo))->SetCheck(BST_CHECKED); 
  CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKHPE);
pBtn->SetCheck(0);
GetDlgItem(IDC_HPEGROUP)->ShowWindow(false);
GetDlgItem(IDC_IVSTATUE)->ShowWindow(false);
GetDlgItem(IDC_OVSTATUE)->ShowWindow(false);
GetDlgItem(IDC_TemSTATUE)->ShowWindow(false);
GetDlgItem(IDC_TemSTATUE)->ShowWindow(false);
GetDlgItem(IDC_FanSTATUE)->ShowWindow(false);
GetDlgItem(IDC_Input)->ShowWindow(false);
GetDlgItem(IDC_Output)->ShowWindow(false);
GetDlgItem(IDC_Tem)->ShowWindow(false);
GetDlgItem(IDC_Fan2)->ShowWindow(false);
GetDlgItem(IDC_PStatue)->ShowWindow(false);
CStatic *pStatic10=(CStatic*)GetDlgItem(IDC_OVFAULT);   
pStatic10->ShowWindow(true);

CStatic *pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT);   
	pStatic11->ShowWindow(true);
    pStatic11=(CStatic*)GetDlgItem(IDC_VMAXWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_VONMAXWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_VOFFMAXWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_VTRACKERR);   
	pStatic11->ShowWindow(true);
//pStatic9-> SetIcon(m_hIcon_open);	
pStatic11=(CStatic*)GetDlgItem(IDC_OVFAULT2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT2);   
	pStatic11->ShowWindow(true);
    pStatic11=(CStatic*)GetDlgItem(IDC_OFF);   
pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCFAULT);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_INOPWARING);   
	pStatic11->ShowWindow(true);

pStatic11=(CStatic*)GetDlgItem(IDC_OCFAULT);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_OCLV);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_OCWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UCFAULT);   
	pStatic11->ShowWindow(true);
    pStatic11=(CStatic*)GetDlgItem(IDC_CSFAULT);   
pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_PLMODE);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_OPFAULT);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_OPWARING);   
	pStatic11->ShowWindow(true);

pStatic11=(CStatic*)GetDlgItem(IDC_OTFAULT);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_OTWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UTWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_UTFAULT);   
	pStatic11->ShowWindow(true);
    pStatic11=(CStatic*)GetDlgItem(IDC_NA);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_NA2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_NA3);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_NA4);   
	pStatic11->ShowWindow(true);

pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING2);   
pStatic11->ShowWindow(true);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT);   
pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT3);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT4);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING3);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING4);   
	pStatic11->ShowWindow(true);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED3);   
pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED4);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input2);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input3);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input4);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input5);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input6);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input7);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input8);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input9);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input10);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input11);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input12);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input13);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input14);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input15);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input16);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input17);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input18);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input19);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input20);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input21);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input22);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input23);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input24);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input25);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input26);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input27);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input28);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input29);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input30);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input31);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input32);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input33);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input34);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input35);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input36);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input37);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input38);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input39);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input40);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input41);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input42);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input43);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input44);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input45);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input46);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input47);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input48);   
	pStatic11->ShowWindow(true);
pStatic11=(CStatic*)GetDlgItem(IDC_Input49);   
	pStatic11->ShowWindow(true);	
	
	
	
	GetDlgItem(IDC_PMGROUP)->ShowWindow(true);
GetDlgItem(IDC_OV)->ShowWindow(true);
GetDlgItem(IDC_OV2)->ShowWindow(true);
GetDlgItem(IDC_OV3)->ShowWindow(true);
GetDlgItem(IDC_OV4)->ShowWindow(true);
GetDlgItem(IDC_OV5)->ShowWindow(true);
GetDlgItem(IDC_OV6)->ShowWindow(true);

}
if(model=="2")
{
  pmbus2=1;
	((CButton*)GetDlgItem(IDC_CHECKHPE))->SetCheck(BST_CHECKED); 
  CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKLenovo);
pBtn->SetCheck(0);
GetDlgItem(IDC_HPEGROUP)->ShowWindow(true);
GetDlgItem(IDC_PMGROUP)->ShowWindow(false);
GetDlgItem(IDC_OV)->ShowWindow(false);
GetDlgItem(IDC_OV2)->ShowWindow(false);
GetDlgItem(IDC_OV3)->ShowWindow(false);
GetDlgItem(IDC_OV4)->ShowWindow(false);
GetDlgItem(IDC_OV5)->ShowWindow(false);
GetDlgItem(IDC_OV6)->ShowWindow(false);
GetDlgItem(IDC_IVSTATUE)->ShowWindow(true);
GetDlgItem(IDC_OVSTATUE)->ShowWindow(true);
GetDlgItem(IDC_TemSTATUE)->ShowWindow(true);
GetDlgItem(IDC_TemSTATUE)->ShowWindow(true);
GetDlgItem(IDC_FanSTATUE)->ShowWindow(true);
GetDlgItem(IDC_Input)->ShowWindow(true);
GetDlgItem(IDC_Output)->ShowWindow(true);
GetDlgItem(IDC_Tem)->ShowWindow(true);
GetDlgItem(IDC_Fan2)->ShowWindow(true);
GetDlgItem(IDC_PStatue)->ShowWindow(true);
CStatic *pStatic10=(CStatic*)GetDlgItem(IDC_OVFAULT);   
pStatic10->ShowWindow(false);

CStatic *pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT);   
	pStatic11->ShowWindow(false);
    pStatic11=(CStatic*)GetDlgItem(IDC_VMAXWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_VONMAXWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_VOFFMAXWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_VTRACKERR);   
	pStatic11->ShowWindow(false);
//pStatic9-> SetIcon(m_hIcon_open);	
pStatic11=(CStatic*)GetDlgItem(IDC_OVFAULT2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT2);   
	pStatic11->ShowWindow(false);
    pStatic11=(CStatic*)GetDlgItem(IDC_OFF);   
pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCFAULT);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_INOPWARING);   
	pStatic11->ShowWindow(false);

pStatic11=(CStatic*)GetDlgItem(IDC_OCFAULT);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_OCLV);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_OCWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UCFAULT);   
	pStatic11->ShowWindow(false);
    pStatic11=(CStatic*)GetDlgItem(IDC_CSFAULT);   
pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_PLMODE);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_OPFAULT);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_OPWARING);   
	pStatic11->ShowWindow(false);

pStatic11=(CStatic*)GetDlgItem(IDC_OTFAULT);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_OTWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UTWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_UTFAULT);   
	pStatic11->ShowWindow(false);
    pStatic11=(CStatic*)GetDlgItem(IDC_NA);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_NA2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_NA3);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_NA4);   
	pStatic11->ShowWindow(false);

pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING2);   
pStatic11->ShowWindow(false);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT);   
pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT3);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT4);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING3);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING4);   
	pStatic11->ShowWindow(false);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED3);   
pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED4);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input2);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input3);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input4);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input5);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input6);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input7);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input8);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input9);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input10);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input11);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input12);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input13);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input14);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input15);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input16);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input17);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input18);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input19);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input20);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input21);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input22);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input23);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input24);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input25);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input26);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input27);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input28);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input29);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input30);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input31);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input32);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input33);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input34);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input35);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input36);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input37);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input38);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input39);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input40);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input41);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input42);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input43);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input44);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input45);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input46);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input47);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input48);   
	pStatic11->ShowWindow(false);
pStatic11=(CStatic*)GetDlgItem(IDC_Input49);   
	pStatic11->ShowWindow(false);












}	
 GetPrivateProfileString(_T("Info"),_T("Address"),_T("B0,B2,B4,B6"),address.GetBuffer(256),256,strFilePath);
address.ReleaseBuffer(256);

pp1=address.GetBuffer(0);
	address.ReleaseBuffer();
	userc1 = new char [address.GetLength()+1]; 
	strcpy_s(userc1,address.GetLength()+1, CT2CA(pp1));
	
	//AfxMessageBox(CString(userc1));
p2=strtok_s(userc1,",",&pnext);
addresszu[0]=CString(p2);
Address[0]=HexToInt(p2);
addressq=1;
//MessageBox(p,"Title",MB_OK);
//Curr[0]=atof(p2);
//strpath[1]=CString(pnext);
//AfxMessageBox(Curr[0]);
strcpy_s(str4,pnext);
i=1;
do{
  p2=strtok_s(str4,",",&pnext);
  //AfxMessageBox(CString(p2));
  if(p2!=NULL)
 {
   //MessageBox(p,"Title",MB_OK);
    //strcpy(cfgpath,p);
	//MessageBox(cfgpath,"Title",MB_OK);  
	 Address[i]=HexToInt(p2);;
	 addresszu[i]=CString(p2);
	 strcpy_s(str4,pnext);
	addressq++;
   i++;
  }
}
 while(p2!=NULL);
/*m_list1.DeleteAllItems();
for(i=0;i<addressq;i++)
{
m_list1.InsertItem(i,addresszu[i]);
}
 */
GetPrivateProfileString(_T("Info"),_T("Name Address"),_T("9A"),tempt.GetBuffer(256),256,strFilePath);
tempt.ReleaseBuffer(256);
pp1=tempt.GetBuffer(0);
	tempt.ReleaseBuffer();
	userc1 = new char [tempt.GetLength()+1]; 
	strcpy_s(userc1,tempt.GetLength()+1, CT2CA(pp1)); 
 modelname=HexToInt(userc1);
GetPrivateProfileString(_T("Info"),_T("Name Length"),_T("0"),tempt.GetBuffer(256),256,strFilePath);
tempt.ReleaseBuffer(256);
pp1=tempt.GetBuffer(0);
	tempt.ReleaseBuffer();
	userc1 = new char [tempt.GetLength()+1]; 
	strcpy_s(userc1,tempt.GetLength()+1, CT2CA(pp1)); 	
 namelength=atoi(userc1);
 
GetPrivateProfileString(_T("Info"),_T("Pri Address"),_T("E3"),tempt.GetBuffer(256),256,strFilePath);
tempt.ReleaseBuffer(256);
pp1=tempt.GetBuffer(0);
	tempt.ReleaseBuffer();
	userc1 = new char [tempt.GetLength()+1]; 
	strcpy_s(userc1,tempt.GetLength()+1, CT2CA(pp1)); 
 priaddress=HexToInt(userc1);	
GetPrivateProfileString(_T("Info"),_T("Pri Length"),_T("0"),tempt.GetBuffer(256),256,strFilePath);
tempt.ReleaseBuffer(256);
pp1=tempt.GetBuffer(0);
	tempt.ReleaseBuffer();
	userc1 = new char [tempt.GetLength()+1]; 
	strcpy_s(userc1,tempt.GetLength()+1, CT2CA(pp1)); 	
prilength=atoi(userc1);
 
GetPrivateProfileString(_T("Info"),_T("Sec Address"),_T("E3"),tempt.GetBuffer(256),256,strFilePath);
tempt.ReleaseBuffer(256);
pp1=tempt.GetBuffer(0);
	tempt.ReleaseBuffer();
	userc1 = new char [tempt.GetLength()+1]; 
	strcpy_s(userc1,tempt.GetLength()+1, CT2CA(pp1)); 
 secaddress=HexToInt(userc1);	
GetPrivateProfileString(_T("Info"),_T("Sec Length"),_T("0"),tempt.GetBuffer(256),256,strFilePath);
tempt.ReleaseBuffer(256);
pp1=tempt.GetBuffer(0);
	tempt.ReleaseBuffer();
	userc1 = new char [tempt.GetLength()+1]; 
	strcpy_s(userc1,tempt.GetLength()+1, CT2CA(pp1)); 	
seclength=atoi(userc1); 

GetPrivateProfileString(_T("Info"),_T("Subaddress"),_T("79,7A,7B,7C"),address.GetBuffer(256),256,strFilePath);
address.ReleaseBuffer(256);
pp1=address.GetBuffer(0);
	address.ReleaseBuffer();
	userc1 = new char [address.GetLength()+1]; 
	strcpy_s(userc1,address.GetLength()+1, CT2CA(pp1));
//AfxMessageBox(CString(userc1));
p2=strtok_s(userc1,",",&pnext);
subaddresszu[0]=CString(p2);
au[0]=CString(p2);
subaddress[0]=HexToInt(p2);
if(subaddress[0]==136)
{
vinno=0;
}
	/*sprintf_s(bufx1,"%d",subaddress[0]);*/
//AfxMessageBox(subaddresszu[0]);
subaddressno=1;
//MessageBox(p,"Title",MB_OK);
//Curr[0]=atof(p2);
//strpath[1]=CString(pnext);
//AfxMessageBox(Curr[0]);
strcpy_s(str4,pnext);
i=1;
do{
  p2=strtok_s(str4,",",&pnext);
  //AfxMessageBox(CString(p2));
  if(p2!=NULL)
 {
   //MessageBox(p,"Title",MB_OK);
    //strcpy(cfgpath,p);
	//MessageBox(cfgpath,"Title",MB_OK);  
	subaddresszu[i]=CString(p2);
	au[i]=CString(p2);
	subaddress[i]=HexToInt(p2);;
	if(subaddress[i]==136)
{
vinno=i;
}
	/*sprintf_s(bufx1,"%d",subaddress[i]);*/
//AfxMessageBox(subaddresszu[i]);
	// subaddresszu[i]=CString(p2);
	 strcpy_s(str4,pnext);
	subaddressno++;
   i++;
  }
}
 while(p2!=NULL);
//m_list1.DeleteAllItems(); 

 int xi;
 xi=m_list1.GetItemCount(); 
 if(xi==0)
 {
	 LONG lStyle;
      lStyle = GetWindowLong(m_list1.m_hWnd, GWL_STYLE);//获取当前窗口style
      lStyle &= ~LVS_TYPEMASK; //清除显示方式位
      lStyle |= LVS_REPORT; //设置style
      SetWindowLong(m_list1.m_hWnd, GWL_STYLE, lStyle);//设置style
 
      DWORD dwStyle = m_list1.GetExtendedStyle();
      dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
      dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
      //dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
       dwStyle |= LVS_SHOWSELALWAYS;//item前生成checkbox控件
	 dwStyle |= LVS_EX_DOUBLEBUFFER;
 	 m_list1.SetExtendedStyle(dwStyle); //设置扩展风格	
	 m_list1.InsertColumn(0,_T("Address"));//添加列 
   m_list1.SetColumnWidth(0, 80);

   
	 for(i=1;i<=subaddressno;i++)
 {
 m_list1.InsertColumn(i,subaddresszu[i-1]);
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,50);
 }
 if(namelength>0)
 {
	 m_list1.InsertColumn(i,_T("Model"));
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,150);
 subaddress[subaddressno]=modelname;
 subaddressno=subaddressno+1;
 i=i+1;
 }
if(prilength>0)
 {
	 m_list1.InsertColumn(i,_T("Pri"));
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,50);
 subaddress[subaddressno]=priaddress;
 subaddressno=subaddressno+1;
 i=i+1;
 } 
if(seclength>0)
 {
	 m_list1.InsertColumn(i,_T("Sec"));
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,50);
 subaddress[subaddressno]=secaddress;
 subaddressno=subaddressno+1;
 i=i+1;
 }  
for(i=0;i<addressq;i++)
{
m_list1.InsertItem(i,addresszu[i]);
}
 } 
 
 if(xi!=0)
 {
     while ( m_list1.DeleteColumn (0));
 m_list1.InsertColumn(0,_T("Address"));//添加列 
   m_list1.SetColumnWidth(0, 80);

   
	 for(i=1;i<=subaddressno;i++)
 {
 m_list1.InsertColumn(i,subaddresszu[i-1]);
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,50);
 }
 if(namelength>0)
 {
	 m_list1.InsertColumn(i,_T("Model"));
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,150);
subaddress[subaddressno]=modelname;	
 subaddressno=subaddressno+1;
 i=i+1;
 }
if(prilength>0)
 {
	 m_list1.InsertColumn(i,_T("Pri"));
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,50);
 subaddress[subaddressno]=priaddress;
 subaddressno=subaddressno+1;
 i=i+1;
 } 
if(seclength>0)
 {
	 m_list1.InsertColumn(i,_T("Sec"));
 //AfxMessageBox(subaddresszu[i-1]);
 m_list1.SetColumnWidth(i,50);
 subaddress[subaddressno]=secaddress;
 subaddressno=subaddressno+1;
 i=i+1;
 }  	
 for(i=0;i<addressq;i++)
{
m_list1.InsertItem(i,addresszu[i]);
}


 }
 
 
 
 
 
 /*LPWSTR   pointer;
 CHeaderCtrl* pListHeader = m_list1.GetHeaderCtrl();
HDITEM hditem;
enum   { sizeOfBuffer = 256 };
TCHAR  lpBuffer[sizeOfBuffer];
 
hditem.mask = HDI_TEXT;
hditem.pszText = lpBuffer;
hditem.cchTextMax = sizeOfBuffer;
 
//pListHeader->GetItem(3, &hditem);
//hditem.pszText = _T("修改的内容");
//pListHeader->SetItem(3, &hditem);


for(i=1;i<=subaddressno;i++)
{
//AfxMessageBox(subaddresszu[i-1]);
	pListHeader->GetItem(i, &hditem);
 pointer=(LPWSTR)(LPCTSTR)subaddresszu[i-1];  
hditem.pszText=pointer;
pListHeader->SetItem(i, &hditem);

}
*/









}












}


void CMFCApplication1Dlg::OnBnClickedBegin()
{
	// TODO: Add your control notification handler code here

	 GetDlgItem(ID_Begin)->EnableWindow(FALSE);
	char * userc;
char *userc1; 
LPCTSTR p1;
LPCTSTR pp1;
	SYSTEMTIME DateTime;
	CTime Time;
 CString path3,type,gg,strneirong,fuhao,fuhao2,timee;
 int xx;

 gg="\\";
 type=".txt";
 wchar_t *path2 = new wchar_t[256];	
GetModuleFileName(NULL,path2,256);
  path3=path2;
 path3=path3.Left(path3.ReverseFind('\\')); 
  Time = CTime::GetCurrentTime();
 path3=path3+gg+Time.Format("%Y%m%d%H%M")+type;
filename=path3; 
 CStdioFile file(path3,CFile::modeCreate|CFile::modeWrite);
fuhao="\r\n";
fuhao2=" ";	
timee="Time";
hmutex=CreateMutex(NULL,false,_T("Mutx"));
CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKHPE);
 int state = pBtn->GetCheck(); 
 if(state==1)
 {
	for(xx=0;xx<subaddressno;xx++)
	{
		//strneirong=strneirong+subaddresszu[xx]+" ";
	strneirong=strneirong+au[xx]+fuhao2;
	}
		strneirong=strneirong+timee+fuhao;
 pp1=strneirong.GetBuffer(0);
	strneirong.ReleaseBuffer();
	
	userc1 = new char [strneirong.GetLength()+1]; 
	strcpy_s(userc1,strneirong.GetLength()+1, CT2CA(pp1));

	file.Write(userc1,strlen(userc1));
 file.Close();
  //AfxMessageBox(CString(path3));
duma=1;
ledpan=1;
MyThread=AfxBeginThread(MyThreadFunction,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
 }
//	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKHPE);
 //int state = pBtn->GetCheck(); 
 if(state==0)
 {
	strneirong="Address ";
	for(xx=0;xx<subaddressno;xx++)
	{
		//strneirong=strneirong+subaddresszu[xx]+" ";
	strneirong=strneirong+au[xx]+fuhao2;
	}
		strneirong=strneirong+timee+fuhao;
 pp1=strneirong.GetBuffer(0);
	strneirong.ReleaseBuffer();
	
	userc1 = new char [strneirong.GetLength()+1]; 
	strcpy_s(userc1,strneirong.GetLength()+1, CT2CA(pp1));

	file.Write(userc1,strlen(userc1));
 file.Close();
  //AfxMessageBox(CString(path3));
duma=1;
ledpan=1;
MyThread=AfxBeginThread(MyThreadFunction1,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
 }

}

void func_binary(unsigned int n)   //定义函数
   {
     int r_value;
     CString zhuantai;
	
	 r_value=n%2;
     if (n>=2)
     {
       func_binary (n/2);
     }
   zhuantai=CString( r_value == 0?'0':'1');
   zhx[xzhuan]=zhuantai;
   xzhuan=xzhuan+1;
   // putchar(r_value == 0?'0':'1');
 
   return;
   }


UINT MyThreadFunction( LPVOID pParam )
{
	CTime Time;
	char * userc;
char *userc1;
char *userc2;
LPCTSTR p1;
LPCTSTR pp1;
unsigned char ArrayToSend[3],ArrayToRead[2];
unsigned char* ss;
CString fuhao,time;
float iv,IC,IP,OV,OC,OP;
int x,y;
FILE *fp;
char sss1[255];
	char buffer[255],buffer1[255];
HWND hwnd; //希望找到资源管理器
fuhao="\r\n";
hwnd=::FindWindow(NULL,_T("PMBUS"));
//AfxMessageBox(CString(buffer));
pp1=filename.GetBuffer(0);
	filename.ReleaseBuffer();
	
	userc1 = new char [filename.GetLength()+1]; 
	strcpy_s(userc1,filename.GetLength()+1, CT2CA(pp1));
 p1=fuhao.GetBuffer(0);
	fuhao.ReleaseBuffer();
	
	userc = new char [fuhao.GetLength()+1]; 
	strcpy_s(userc,fuhao.GetLength()+1, CT2CA(p1));
	fopen_s(&fp,userc1,"a+");
	SelectBySerialNumber(SerialNumbers[0]);
	do
{
for(x=0;x<addressq;x++)
{
sprintf_s(buffer, "%02X",Address[x]);
fseek(fp,0L,2);
strcat_s(buffer," ");
fputs(buffer,fp);
for(y=0;y<subaddressno;y++)
{
ArrayToSend[0]=HexToInt("00");
ArrayToSend[1]=subaddress[y];
//ArrayToSend[2]=(256-int(subaddress[y])-int(Address[x]))%100;
ArrayToSend[2]=256-(int(subaddress[y])+int(Address[x]))%256;
ErrorCode=I2CWrite(Address[x],3,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],2,(unsigned char *)ArrayToRead,1);
sprintf_s(buffer, "%02X%02X",ArrayToRead[1],ArrayToRead[0]);
if(int(subaddress[y])==16)
{
//AfxMessageBox(CString(buffer));
iv=float(StrToNumber16(buffer))/32;
sprintf_s(buffer, "%.2f",iv);
//AfxMessageBox(CString(buffer));
}
if(int(subaddress[y])==17)
{
IC=float(StrToNumber16(buffer))/64;
sprintf_s(buffer, "%.3f",IC);
//AfxMessageBox(CString(buffer));
}	
if(int(subaddress[y])==18)
{
IP=float(StrToNumber16(buffer));
sprintf_s(buffer, "%.3f",IP);
//AfxMessageBox(CString(buffer));
}	
//AfxMessageBox(CString(buffer));
if(int(subaddress[y])==32)
{
OV=float(StrToNumber16(buffer))/256;
sprintf_s(buffer, "%.3f",OV);
//AfxMessageBox(CString(buffer));
}	
if(int(subaddress[y])==33)
{
OC=float(StrToNumber16(buffer))/64;
sprintf_s(buffer, "%.3f",OC);
//AfxMessageBox(CString(buffer));
}	
if(int(subaddress[y])==34)
{
OP=float(StrToNumber16(buffer));
sprintf_s(buffer, "%.3f",OP);
//AfxMessageBox(CString(buffer));
}
if((strcmp(buffer,"000B")==0)&&(int(subaddress[y])==2))
{
	ledpan=0;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA1,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"0000")==0)&&(int(subaddress[y])==2))
{
	ledpan=1;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA1,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"8001")==0)&&(int(subaddress[y])==2))
{
	ledpan=2;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA1,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"8005")==0)&&(int(subaddress[y])==2))
{
	ledpan=3;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA1,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"8004")==0)&&(int(subaddress[y])==2))
{
	ledpan=4;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA1,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"8008")==0)&&(int(subaddress[y])==2))
{
	ledpan=5;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA1,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}


tx=x;
tt=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA,  // 发送自己的窗口消息   
           (WPARAM)&buffer,     // 设置发送的内容   
             NULL);
fseek(fp,0L,2);
strcat_s(buffer," ");
fputs(buffer,fp);


}
SYSTEMTIME t;
char t_y[256],t_y2[256],t_y3[256];
GetLocalTime(&t);//调用获取系统时间api
if(t.wMilliseconds<10)
{
strcpy_s(t_y3,"00");
sprintf_s(t_y2,"%d",t.wMilliseconds);
strcat_s(t_y3,t_y2);
}
if((t.wMilliseconds>=10)&&(t.wMilliseconds<100))	
{
strcpy_s(t_y3,"0");
sprintf_s(t_y2,"%d",t.wMilliseconds);
strcat_s(t_y3,t_y2);
}
if(t.wMilliseconds>=100)	
{
sprintf_s(t_y3,"%d",t.wMilliseconds);
}
	sprintf_s(t_y,"%04d%02d%02d%02d%02d%02d",t.wYear,t.wMonth,t.wDay,t.wHour,
     t.wMinute,t.wSecond);  
strcat_s(t_y,t_y3); 
/*Time = CTime::GetCurrentTime();
time=Time.Format("%Y%m%d%H%M%S");
pp1=time.GetBuffer(0);
	time.ReleaseBuffer();
	
	userc2 = new char [time.GetLength()+1]; 
	strcpy_s(userc2,time.GetLength()+1, CT2CA(pp1));*/

fseek(fp,0L,2);
fputs(t_y,fp);
fseek(fp,0L,2);
fputs(userc,fp);
//fputs("\r\n",fp);
}
}while(duma==1);

fclose(fp);


return 0;
}

UINT MyThreadFunction1( LPVOID pParam )
{
	CTime Time;
	
	char * userc;
char *userc1;
char *userc2;
char *buffername;
LPCTSTR p1;
LPCTSTR pp1;
unsigned char ArrayToSend[3],ArrayToRead[2],ArrayToRead1[50];
unsigned char* ss;

CString fuhao,time,kong,ling,zhongjian[256],nx[256],tn;
float iv,IC,IP,OV,OC,OP,EE[10],fproll[2],faccm[2],fdt[2],ft1,ft2,EEx;
int x,y,lx,NN,yy,proll[2],accm[2],dt[2],lxx,lx3,count,px;
FILE *fp;
char sss1[255];
	char buffer[255],buffer1[255],bufferx[255],buffroll[256],buffaccm[256],buffn[256];
char *buffn1;
	HWND hwnd; //希望找到资源管理器
		int mx;
CString ch,ch1;
px=0;
fuhao="\r\n";
kong="";
hwnd=::FindWindow(NULL,_T("PMBUS"));
//AfxMessageBox(CString(buffer));
pp1=filename.GetBuffer(0);
	filename.ReleaseBuffer();
	
	userc1 = new char [filename.GetLength()+1]; 
	strcpy_s(userc1,filename.GetLength()+1, CT2CA(pp1));
 p1=fuhao.GetBuffer(0);
	fuhao.ReleaseBuffer();
	
	userc = new char [fuhao.GetLength()+1]; 
	strcpy_s(userc,fuhao.GetLength()+1, CT2CA(p1));
	fopen_s(&fp,userc1,"a+");
	do
{
	WaitForSingleObject(hmutex,INFINITE);
	for(x=0;x<addressq;x++)
{
sprintf_s(buffer, "%02X",Address[x]);
fseek(fp,0L,2);
strcat_s(buffer," ");
fputs(buffer,fp);
for(y=0;y<subaddressno;y++)
{
//ArrayToSend[0]=HexToInt("00");
/*ArrayToSend[0]=subaddress[y];
//ArrayToSend[2]=(256-int(subaddress[y])-int(Address[x]))%100;
ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],2,(unsigned char *)ArrayToRead,1);
sprintf_s(buffer, "%02X%02X",ArrayToRead[1],ArrayToRead[0]);*/
	if(px==0)
	{
	px=px+1;
	}
	if((int(subaddress[y])==121)||(int(subaddress[y])==141)||(int(subaddress[y])==142)||(int(subaddress[y])==143)||(int(subaddress[y])==144)||(int(subaddress[y])==136)||(int(subaddress[y])==137)||(int(subaddress[y])==151)||(int(subaddress[y])==139)||(int(subaddress[y])==140)||(int(subaddress[y])==150)||(int(subaddress[y])==143))
{
ArrayToSend[0]=subaddress[y];
ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],2,(unsigned char *)ArrayToRead,1);
sprintf_s(buffer, "%02X%02X",ArrayToRead[1],ArrayToRead[0]);
//AfxMessageBox(CString(buffer));
}
else
{
	if((int(subaddress[y])!=134)&&(int(subaddress[y])!=135)&&(int(subaddress[y])!=int(modelname))&&(int(subaddress[y])!=int(priaddress))&&(int(subaddress[y])!=int(secaddress)))
{
	ArrayToSend[0]=subaddress[y];
ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],1,(unsigned char *)ArrayToRead,1);
sprintf_s(buffer, "%02X",ArrayToRead[0]);
//AfxMessageBox(CString(buffer));
}
}	

if((int(subaddress[y])==int(modelname))&&(px==1))
{
ch1="";
	if(namelength>2)
{
	ArrayToSend[0]=subaddress[y];
	ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],namelength,(unsigned char *)ArrayToRead1,1);
for(mx=0;mx<namelength;mx++)
{
	ch.Format(_T("%c"),ArrayToRead1[mx]);
ch1=ch1+ch;
}
p1=ch1.GetBuffer(0);
	ch1.ReleaseBuffer();
	
	buffername = new char [ch1.GetLength()+1]; 
	strcpy_s(buffername,ch1.GetLength()+1, CT2CA(p1));
	strcpy_s(buffer,buffername);
	}

}

if((int(subaddress[y])==int(priaddress))&&(px==1))
{
ch1="";
	
if(prilength>2)
{
	ArrayToSend[0]=subaddress[y];
	sprintf_s(buffer, "%02X",ArrayToSend[0]);
	//AfxMessageBox(CString(buffer));
	ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],prilength,(unsigned char *)ArrayToRead1,1);
for(mx=0;mx<prilength;mx++)
{
	//AfxMessageBox(ArrayToRead1[mx]);
	ch.Format(_T("%c"),ArrayToRead1[mx]);
ch1=ch1+ch;
}
p1=ch1.GetBuffer(0);
	ch1.ReleaseBuffer();
	
	buffername = new char [ch1.GetLength()+1]; 
	strcpy_s(buffername,ch1.GetLength()+1, CT2CA(p1));
	strcpy_s(buffer,buffername);
	}

}
if((int(subaddress[y])==int(secaddress))&&(px==1))
{
ch1="";
	if(seclength>2)
{
	ArrayToSend[0]=subaddress[y];
	ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],seclength,(unsigned char *)ArrayToRead1,1);
for(mx=0;mx<seclength;mx++)
{
	ch.Format(_T("%c"),ArrayToRead1[mx]);
ch1=ch1+ch;
}
p1=ch1.GetBuffer(0);
	ch1.ReleaseBuffer();
	
	buffername = new char [ch1.GetLength()+1]; 
	strcpy_s(buffername,ch1.GetLength()+1, CT2CA(p1));
	strcpy_s(buffer,buffername);
	}

}



if((int(subaddress[y])==134)||(int(subaddress[y])==135))
{
		for(lx3=0;lx3<10;lx3++)
	{
	
	ArrayToSend[0]=subaddress[y];
	ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],8,(unsigned char *)ArrayToRead1,1);
//sprintf_s(buffer, "%02X%02X%02X%02X%02X%02X",ArrayToRead1[6],ArrayToRead1[5],ArrayToRead1[4],ArrayToRead1[3],ArrayToRead1[2],ArrayToRead1[1]);
sprintf_s(buffaccm, "%02X%02X",ArrayToRead1[2],ArrayToRead1[1]);
sprintf_s(buffroll, "%02X",ArrayToRead1[3]);
sprintf_s(buffn, "%02X%02X%02X",ArrayToRead1[6],ArrayToRead1[5],ArrayToRead1[4]);

//AfxMessageBox(CString(buffn));
proll[0]=StrToNumber16(buffroll);
//fproll[0]=float(proll[0]);
accm[0]=StrToNumber16(buffaccm);
dt[0]=StrToNumber16(buffn);
if(dt[0]>16777215)	
{dt[0]=0;}
	//}
/*sprintf_s(buffer, "%.3f",float(fdt[0]));
AfxMessageBox(CString(buffer));
sprintf_s(buffer, "%.3f",float(fdt[1]));
AfxMessageBox(CString(buffer));*/
	/*for(lxx=0;lxx<10;lxx++)
	{
	ArrayToRead1[lxx]=0;
	}*/
//delay(1000);
count=0;
do
{
ErrorCode=I2CWrite(Address[x],1,(unsigned char *)ArrayToSend,0);
ErrorCode=I2CRead(Address[x],8,(unsigned char *)ArrayToRead1,1);
//sprintf_s(buffer, "%02X%02X%02X%02X%02X%02X",ArrayToRead1[6],ArrayToRead1[5],ArrayToRead1[4],ArrayToRead1[3],ArrayToRead1[2],ArrayToRead1[1]);
sprintf_s(buffaccm, "%02X%02X",ArrayToRead1[2],ArrayToRead1[1]);
sprintf_s(buffroll, "%02X",ArrayToRead1[3]);
sprintf_s(buffn, "%02X%02X%02X",ArrayToRead1[6],ArrayToRead1[5],ArrayToRead1[4]);
proll[1]=StrToNumber16(buffroll);
//fproll[1]=float(proll[1]);
accm[1]=StrToNumber16(buffaccm);
//faccm[1]=float(accm[1]);
dt[1]=StrToNumber16(buffn);
if(dt[1]>16777215)	
{dt[1]=0;}
count++;
}while((dt[0]==dt[1])&&(count<50));
//fdt[1]=float(dt[1]);
//sprintf_s(buffer, "%.3f",float(accm[1]));
//AfxMessageBox(CString(buffer));
//delay(5000);
if(count<50)
{EE[lx3]=float(((proll[1]*32767+accm[1])-(proll[0]*32767+accm[0])))/(dt[1]-dt[0]);}
else
{
EE[lx3]=0;
}
//e2=accm[1]-accm[0];
//EE=ft2-ft1;
	}
	EEx=0;
	for(lxx=0;lxx<10;lxx++)
	{
	EEx=EEx+EE[lxx];
	}
	EEx=EEx/10;
	sprintf_s(buffer, "%.3f",EEx);
//AfxMessageBox(CString(buffer));

	}

if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==122))
{
hang=x;
lie=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA3,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
zutai=DECToBIN(DEC(CString(buffer)));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
ledpan=0;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}

if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==124))
{
hang=x;
lie=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA3,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
zutai=DECToBIN(DEC(CString(buffer)));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
ledpan=2;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}

if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==123))
{
hang=x;
lie=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA3,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
zutai=DECToBIN(DEC(CString(buffer)));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
ledpan=3;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}

if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==125))
{
hang=x;
lie=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA3,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
zutai=DECToBIN(DEC(CString(buffer)));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
ledpan=4;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}

if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==129))
{
hang=x;
lie=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA3,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
zutai=DECToBIN(DEC(CString(buffer)));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
ledpan=5;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}


if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==130))
{
hang=x;
lie=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA3,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
zutai=DECToBIN(DEC(CString(buffer)));
for(lx=0;lx<8;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
ledpan=6;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}
NN=0;
if((int(subaddress[y])==136)||(int(subaddress[y])==137)||(int(subaddress[y])==151)||(int(subaddress[y])==140)||(int(subaddress[y])==150)||(int(subaddress[y])==144)||(int(subaddress[y])==141)||(int(subaddress[y])==142)||(int(subaddress[y])==143))
{
zutai=DECToBIN(DEC(CString(buffer)));
//AfxMessageBox(zutai);
for(lx=0;lx<16;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}
if(zutais[15]=="1")
{
for(lx=0;lx<5;lx++)
{
	if(zutais[11+lx]=="1")
	{
	NN=NN+pow(2,lx);
	}

}

}
NN=NN-1;
//sprintf_s(bufferx, "%d",NN);
//AfxMessageBox(CString(bufferx));
func_binary (NN);
xzhuan=0;
NN=0;
for(lx=0;lx<5;lx++)
{
//AfxMessageBox(zhx[lx]);
if(zhx[lx]=="0")
{
NN=NN+pow(2,4-lx);
}

}
if(zutais[15]=="0")
{
	NN=0;
	for(lx=0;lx<5;lx++)
{
	if(zutais[11+lx]=="1")
	{
	NN=NN+pow(2,lx);
	}

}

}




yy=0;
for(lx=0;lx<11;lx++)
{
if(zutais[lx]=="1")
	{
	yy=yy+pow(2,lx);
	}
}
if(int(subaddress[y])==144)
{
if(zutais[15]=="1")
{
	iv=float(yy)/float(pow(2,NN));
sprintf_s(buffer, "%d",int(iv));
}
if(zutais[15]=="0")
{
	iv=float(yy*pow(2,NN));
sprintf_s(buffer, "%d",int(iv));
}

}
else
{
if(zutais[15]=="1")
{
	iv=float(yy)/float(pow(2,NN));
sprintf_s(buffer, "%.3f",iv);
}
if(zutais[15]=="0")
{
	iv=float(yy*pow(2,NN));
sprintf_s(buffer, "%.3f",iv);
}

}

}


NN=0;
if(int(subaddress[y])==139)
{
zutai=DECToBIN(DEC(CString(buffer)));
//AfxMessageBox(zutai);
for(lx=0;lx<16;lx++)
{
	if(lx<=(zutai.GetLength()-1))
	{
		zutais[lx]=zutai.GetAt(zutai.GetLength()-1-lx);

	}
if(lx>(zutai.GetLength()-1))
{
zutais[lx]="0";
}
//AfxMessageBox(zutais[lx]);
}

yy=0;
for(lx=0;lx<16;lx++)
{
if(zutais[lx]=="1")
	{
	yy=yy+pow(2,lx);
	}
}


	iv=float(yy)/512;
sprintf_s(buffer, "%.3f",iv);




}
















if(((strcmp(buffer,"0000")==0)||(strcmp(buffer,"0002")==0)||(strcmp(buffer,"0843")==0))&&(int(subaddress[y])==121))
{
	ledpan=1;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA4,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);



}
//if((strcmp(buffer,"10")==0)&&(int(subaddress[y])==122))
/*else
{
ledpan=7;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);

}*/


/*if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==123))
{
	ledpan=3;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==125))
{
	ledpan=4;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
if((strcmp(buffer,"00")!=0)&&(int(subaddress[y])==129))
{
	ledpan=5;
	SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA2,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
}
*/






tx=x;
tt=y+1;
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA,  // 发送自己的窗口消息   
           (WPARAM)&buffer,     // 设置发送的内容   
             NULL);
fseek(fp,0L,2);
strcat_s(buffer," ");
fputs(buffer,fp);


}

SYSTEMTIME t;
char t_y[256],t_y2[256],t_y3[256];
GetLocalTime(&t);//调用获取系统时间api
if(t.wMilliseconds<10)
{
strcpy_s(t_y3,"00");
sprintf_s(t_y2,"%d",t.wMilliseconds);
strcat_s(t_y3,t_y2);
}
if((t.wMilliseconds>=10)&&(t.wMilliseconds<100))	
{
strcpy_s(t_y3,"0");
sprintf_s(t_y2,"%d",t.wMilliseconds);
strcat_s(t_y3,t_y2);
}
if(t.wMilliseconds>=100)	
{
sprintf_s(t_y3,"%d",t.wMilliseconds);
}
	sprintf_s(t_y,"%04d%02d%02d%02d%02d%02d",t.wYear,t.wMonth,t.wDay,t.wHour,
     t.wMinute,t.wSecond);  
strcat_s(t_y,t_y3);



/*Time = CTime::GetCurrentTime();
time=Time.Format("%Y%m%d%H%M%S%Mi");
pp1=time.GetBuffer(0);
	time.ReleaseBuffer();
	
	userc2 = new char [time.GetLength()+1]; 
	strcpy_s(userc2,time.GetLength()+1, CT2CA(pp1));*/
fseek(fp,0L,2);
fputs(t_y,fp);
fseek(fp,0L,2);
fputs(userc,fp);
//fputs("\r\n",fp);
}
 ReleaseMutex(hmutex);
}while(duma==1);

fclose(fp);


return 0;
}

LRESULT CMFCApplication1Dlg::OnUpdateMyData6(WPARAM wParam, LPARAM lParam)
{
	HWND buttonhWnd;
	buttonhWnd=::GetDlgItem(m_hWnd,IDC_Demo);
	 
	 ::SendMessage(buttonhWnd, BM_CLICK, 0, 0);  

return 0;
}
LRESULT CMFCApplication1Dlg::OnUpdateMyData(WPARAM wParam, LPARAM lParam)
{
/*int sp;
int count=0;
CString* strEdit = (CString*)wParam;  
char *str22= (char*)wParam;
//sp=m_ListBox1.GetCurSel();
//m_ListBox1.InsertString(sp,(LPCTSTR)strEdit);  
int num = MultiByteToWideChar(0,0,str22,-1,NULL,0);
wchar_t *wide = new wchar_t[num];
MultiByteToWideChar(0,0,str22,-1,wide,num);
count=m_ListBox1.GetCount();
m_ListBox1.SetCurSel(count-2);
m_ListBox1.InsertString(sp2,wide);  */
char *str22= (char*)wParam;

/*int num = MultiByteToWideChar(0,0,str22,-1,NULL,0);
wchar_t *wide = new wchar_t[num];
MultiByteToWideChar(0,0,str22,-1,wide,num);*/
//if(tt==1)
//{
	m_list1.SetItemText(tx,tt,CString(str22));		
//}
	//;
	//m_list1.GetItemText(0,15);
	//AfxMessageBox(GetInpVin());
	
	
	
	
	
return 0; 
}

LRESULT CMFCApplication1Dlg::OnUpdateMyData3(WPARAM wParam, LPARAM lParam)
{
	m_list1.SetColor(hang,lie,RGB(255,0,0));

	
	
	return 0; 
}

LRESULT CMFCApplication1Dlg::OnUpdateMyData4(WPARAM wParam, LPARAM lParam)
{
	int x,y;
	for(x=0;x<addressq;x++)
	{
	for(y=0;y<subaddressno;y++)
	{
		m_list1.SetColor(x,y+1,RGB(255,255,255));
	}
	
	}
	return 0; 
}



LRESULT CMFCApplication1Dlg::OnUpdateMyData1(WPARAM wParam, LPARAM lParam)
{
	if(ledpan==0)
	{
	/*	CStatic *pStatic=(CStatic*)GetDlgItem(IDC_IVUVP);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
CStatic *pStatic5=(CStatic*)GetDlgItem(IDC_Normal);   
	pStatic5-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic5-> SetIcon(m_hIcon_close);	*/
	CStatic *pStatic=(CStatic*)GetDlgItem(IDC_IVSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("InPut UVP"));
	}
if(ledpan==1)
	{
CStatic *pStatic6=(CStatic*)GetDlgItem(IDC_IVSTATUE);   
	pStatic6-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic6-> SetIcon(m_hIcon_open);  	
CStatic *pStatic7=(CStatic*)GetDlgItem(IDC_OVSTATUE);   
	pStatic7-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic7-> SetIcon(m_hIcon_open);	
CStatic *pStatic8=(CStatic*)GetDlgItem(IDC_TemSTATUE);   
	pStatic8-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic8-> SetIcon(m_hIcon_open);	
CStatic *pStatic9=(CStatic*)GetDlgItem(IDC_FanSTATUE);   
	pStatic9-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic9-> SetIcon(m_hIcon_open);	
GetDlgItem(IDC_PStatue)->SetWindowText(_T("Normal"));
//GetDlgItem(IDC_PStatue)->SetWindowText(_T("Normal"));	
	










}
	if(ledpan==2)
	{
		CStatic *pStatic=(CStatic*)GetDlgItem(IDC_OVSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("OutPut OVP"));	
	}	
	if(ledpan==3)
	{
		/*CStatic *pStatic=(CStatic*)GetDlgItem(IDC_Normal);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
CStatic *pStatic5=(CStatic*)GetDlgItem(IDC_SOT);   
	pStatic5-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic5-> SetIcon(m_hIcon_close);	*/
	
CStatic *pStatic=(CStatic*)GetDlgItem(IDC_TemSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("SOTP"));	
	}	
	if(ledpan==4)
	{
	/*	CStatic *pStatic=(CStatic*)GetDlgItem(IDC_Normal);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
CStatic *pStatic5=(CStatic*)GetDlgItem(IDC_POT);   
	pStatic5-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic5-> SetIcon(m_hIcon_close);	
*/
CStatic *pStatic=(CStatic*)GetDlgItem(IDC_TemSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("POTP"));
	}	
	if(ledpan==5)
	{
		CStatic *pStatic=(CStatic*)GetDlgItem(IDC_OVSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("OutPut OCP"));
	}		
	

	
	
	
	
	
	
return 0; 
}

void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	duma=0;
	
		CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
duma=0;
GetDlgItem(ID_Begin)->EnableWindow(TRUE);
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE; 
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CMFCApplication1Dlg::OnClickedCheckhpe()
{
	// TODO: Add your control notification handler code here

CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKLenovo);
 int state = pBtn->GetCheck();
 if(state==0)
 {
 pBtn->SetCheck(1);
 }
 if(state==1)
 {
 pBtn->SetCheck(0);
 }

}


void CMFCApplication1Dlg::OnClickedChecklenovo()
{
	// TODO: Add your control notification handler code here
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKHPE);
 int state = pBtn->GetCheck();
 if(state==0)
 {
 pBtn->SetCheck(1);
 }
 if(state==1)
 {
 pBtn->SetCheck(0);
 }


}


/*void CMFCApplication1Dlg::OnBnClickedPause()
{
	// TODO: Add your control notification handler code here
//MyThread->SuspendThread();






}
*/
LRESULT CMFCApplication1Dlg::OnUpdateMyData2(WPARAM wParam, LPARAM lParam)
{
	int lx;
	CStatic *pStatic;
	if(ledpan==0)
	{
	
		if(zutais[0]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_VTRACKERR);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[1]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_VOFFMAXWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[2]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_VONMAXWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[3]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_VMAXWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[4]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UVFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[5]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UVWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[6]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OVWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
				if(zutais[7]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OVFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}				
	
	
	
	}
if(ledpan==1)
	{
CStatic *pStatic10=(CStatic*)GetDlgItem(IDC_OVFAULT);   
	pStatic10-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic10-> SetIcon(m_hIcon_open);
CStatic *pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_VMAXWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_VONMAXWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_VOFFMAXWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_VTRACKERR);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);	
pStatic11=(CStatic*)GetDlgItem(IDC_OVFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OVWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UVFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_OFF);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_INOCWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_INOPWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OCFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OCLV);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OCWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UCFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_CSFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_PLMODE);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OPFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OPWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OTFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_OTWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UTWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_UTFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_NA);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_NA2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_NA3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_NA4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANFAULT4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANWARING4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
    pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED3);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_FANSPEED4);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRFAULT2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
pStatic11=(CStatic*)GetDlgItem(IDC_AIRWARING2);   
	pStatic11-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic11-> SetIcon(m_hIcon_open);
}
	if(ledpan==2)
	{
	
		if(zutais[0]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_INOPWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[1]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_INOCWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[2]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_INOCFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[3]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OFF);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[4]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UVFAULT2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[5]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UVWARING2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[6]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OVWARING2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
				if(zutais[7]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OVFAULT2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}				
	
	
	
	}

if(ledpan==3)
	{
	
		if(zutais[0]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OPWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[1]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OPFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[2]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_PLMODE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[3]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_CSFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[4]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UCFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[5]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OCWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[6]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OCLV);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
				if(zutais[7]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OCFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}				
	
	
	
	}	
	
if(ledpan==4)
	{
	
		if(zutais[0]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_NA4);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[1]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_NA3);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[2]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_NA2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[3]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_NA);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[4]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UTFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[5]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_UTWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[6]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OTWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
				if(zutais[7]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_OTFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}				
	
	
	
	}	
	
if(ledpan==5)
	{
	
		if(zutais[0]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_AIRWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[1]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_AIRFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[2]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANSPEED2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[3]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANSPEED);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[4]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANWARING2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[5]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANWARING);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[6]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANFAULT2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
				if(zutais[7]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANFAULT);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}				
	
	
	
	}		
	
if(ledpan==6)
	{
	
		if(zutais[0]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_AIRWARING2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[1]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_AIRFAULT2);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[2]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANSPEED4);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[3]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANSPEED3);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[4]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANWARING4);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
		if(zutais[5]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANWARING3);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
			if(zutais[6]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANFAULT4);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}
				if(zutais[7]=="1")	
		{
	pStatic=(CStatic*)GetDlgItem(IDC_FANFAULT3);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
		}				
	
	
	
	}			
	
	
	/*if(ledpan==2)
	{
		CStatic *pStatic=(CStatic*)GetDlgItem(IDC_OVSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("OutPut UVP"));	
	}	*/
	/*if(ledpan==3)
	{
		CStatic *pStatic=(CStatic*)GetDlgItem(IDC_OVSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("IOUT ERR"));
	}	
	if(ledpan==4)
	{
		CStatic *pStatic=(CStatic*)GetDlgItem(IDC_TemSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("Tempture ERR"));
	}	
	if(ledpan==5)
	{
			CStatic *pStatic=(CStatic*)GetDlgItem(IDC_FanSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("Fan Err"));
	}		
	
	if(ledpan==6)
	{
			CStatic *pStatic=(CStatic*)GetDlgItem(IDC_IVSTATUE);   
	pStatic-> ModifyStyle(0x0,SS_ICON|SS_CENTERIMAGE);   
pStatic-> SetIcon(m_hIcon_close);
	GetDlgItem(IDC_PStatue)->SetWindowText(_T("InPut Err"));
	}	
	*/
	
	
	
	
	
return 0; 
}

HBRUSH CMFCApplication1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

CString tr;
	// TODO:  Return a different brush if the default is not desired
if (pWnd->GetDlgCtrlID()==IDC_PStatue) 
	{
	
//pDC->SetBkMode(TRANSPARENT);//

GetDlgItemText(IDC_PStatue,tr);
if((tr!="Normal")&&(tr!="Wait"))
{
	pDC->SetTextColor(RGB(255,0,0));	
}
 if(tr=="Normal")
		{
			pDC->SetTextColor(RGB(0,255,0));
		}
 if(tr=="Wait")
		{
			pDC->SetTextColor(RGB(0,0,255));
		}
		 

	/*if(tr=="Shop_FAIL")
		{
			pDC->SetTextColor(RGB(255,0,0));
		}	
	if(tr=="Debug")
		{
			pDC->SetTextColor(RGB(0,0,255));
		}*/		
	
	
//return (HBRUSH)::GetStockObject(NULL_BRUSH);

	}		




return hbr;
}




/*void CMFCApplication1Dlg::OnCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//@TN
		*pResult = 0;
	// TODO: Add your control notification handler code here


	*pResult = 0;
}
*/

CString CMFCApplication1Dlg::GetInpCurr()
{
CString inpcurr;
inpcurr=m_list1.GetItemText(0,0);


return inpcurr; 

}

CString CMFCApplication1Dlg::GetInpVin()
{
CString inpvin;
char no[256];
if(pmbus1==1)
{
	//sprintf_s(no,"%d",vinno);
	//AfxMessageBox(CString(no));
	inpvin=m_list1.GetItemText(0,15);
	VINREAD=inpvin;
	//AfxMessageBox(m_list1.GetItemText(0,15));
}

return VINREAD;

}


void CAboutDlg::OnChart()
{
	// TODO: Add your command handler code here
}


void CMFCApplication1Dlg::OnChart()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("33"));
Graph chart;
chart.DoModal();
//AfxMessageBox(_T("33"));
/*if(chart.DoModal())
{




}*/




}


void CMFCApplication1Dlg::OnBnClickedDemo()
{
	// TODO: Add your control notification handler code here
//AfxMessageBox(_T("33"));
/*HWND hWnd1;
CString inpvin;
char * userc;
char *userc1; 
LPCTSTR p1;
LPCTSTR pp1;
char buffer[256];	
inpvin=m_list1.GetItemText(0,vinno+1);	
 pp1=inpvin.GetBuffer(0);
	inpvin.ReleaseBuffer();
	userc1 = new char [inpvin.GetLength()+1]; 
	strcpy_s(userc1,inpvin.GetLength()+1, CT2CA(pp1));  
	strcpy_s(buffer,userc1);
	hWnd1=::FindWindow(NULL,_T("Chart"));	
	::SendMessage(hWnd1, WM_MYUPDATEDATA7,(WPARAM)&buffer,NULL);*/
	start2=1;
	MyThread8=AfxBeginThread(MyThreadFunction8,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
}

UINT MyThreadFunction8( LPVOID pParam )
{
HWND hWnd1,hwnd;

char * userc;
char *userc1; 
LPCTSTR p1;
LPCTSTR pp1;
char buffer[256];	
do
{
hwnd=::FindWindow(NULL,_T("PMBUS"));
SendMessage(hwnd, // 获得主窗口在句柄   
           WM_MYUPDATEDATA8,  // 发送自己的窗口消息   
           NULL,     // 设置发送的内容   
             NULL);
 pp1=VINREAD.GetBuffer(0);
	VINREAD.ReleaseBuffer();
	userc1 = new char [VINREAD.GetLength()+1]; 
	strcpy_s(userc1,VINREAD.GetLength()+1, CT2CA(pp1));  
	strcpy_s(buffer,userc1);
//	AfxMessageBox(CString(buffer));
	hWnd1=::FindWindow(NULL,_T("Chart"));	
	::SendMessage(hWnd1, WM_MYUPDATEDATA7,(WPARAM)&buffer,NULL);
}while(start2==1);



return 0;
}

LRESULT CMFCApplication1Dlg::OnUpdateMyData8(WPARAM wParam, LPARAM lParam)
{
	VINREAD=m_list1.GetItemText(0,vinno);	
	//AfxMessageBox(VINREAD);
return 0;
}

void CMFCApplication1Dlg::OnBnClickedDemo2()
{
	// TODO: Add your control notification handler code here
start2=0;
}
