// MyListctrl.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MyListctrl.h"


// MyListctrl

IMPLEMENT_DYNAMIC(MyListctrl, CListCtrl)

MyListctrl::MyListctrl()
{

 m_iRow = -1;  //这里我们定义了三个成员变量，分别用于表示单元格的“行号”，“列号”，“字体” 在构造函数中初始化他们。
    m_iCol = -1;
    m_Font = NULL;
}

MyListctrl::~MyListctrl()
{
 if ( m_Font )    delete m_Font;
}


BEGIN_MESSAGE_MAP(MyListctrl, CListCtrl)
 ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnNMCustomdraw)
END_MESSAGE_MAP()



// MyListctrl message handlers

void MyListctrl::PreSubclassWindow() 
{
    // TODO: Add your specialized code here and/or call the base class
    CListCtrl::PreSubclassWindow();
}
void   MyListctrl::OnNMCustomdraw(NMHDR   *pNMHDR,   LRESULT   *pResult)
{
 NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR ); 

*pResult = CDRF_DODEFAULT;
    
    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
    
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
    {
        *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
    {
        // This is the notification message for an item. We'll request
        // notifications before each subitem's prepaint stage.
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
    }
else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
 {                                                                         //我们就可以判断“行”和“列”，从而来设置文字颜色和文字背景颜色了。
        // This is the prepaint stage for a subitem. Here's where we set the
        // item's text and background colors. Our return value will tell 
        // Windows to draw the subitem itself, but it will use the new colors
        // we set here. 
        if ( m_iCol == pLVCD->iSubItem && m_iRow == pLVCD->nmcd.dwItemSpec)
        {
            pLVCD->clrTextBk = m_Color;
            pLVCD->clrText = m_TextColor;
            
            //SetFont(m_Font, false);
        }
        else
        {
            pLVCD->clrTextBk = 16777215;//如果不是选择的“行”和“列”就设置成系统默认的那种颜色。
            pLVCD->clrText = 0;
        }
        //SetFont(m_Font, false);
        // Store the colors back in the NMLVCUSTOMDRAW struct.
        // Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
    }
}
void MyListctrl::SetColor(int iRow, int iCol, COLORREF color)
{
    m_iRow = iRow;
    m_iCol = iCol;
    m_Color = color;

}

void MyListctrl::SetSunItemFont(LOGFONT font, COLORREF color, long lsize)
{
    if ( m_Font )    delete m_Font;    //删除旧字体
    m_Font = new CFont;
    m_Font->CreateFontIndirect(&font);

    m_TextColor = color;
    m_TextSize = lsize;
}



