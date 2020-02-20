#pragma once


// MyListctrl

class MyListctrl : public CListCtrl
{
	DECLARE_DYNAMIC(MyListctrl)




public:
	MyListctrl();
	virtual ~MyListctrl();
protected:
	virtual void PreSubclassWindow() ;
protected:
	DECLARE_MESSAGE_MAP()

public:
afx_msg void OnNMCustomdraw(NMHDR   *pNMHDR,   LRESULT   *pResult);

public:
	void SetColor(int row,int col,COLORREF color);
	void SetSunItemFont(LOGFONT front,COLORREF color,long size);
	int m_iRow;
	int m_iCol;
	COLORREF m_Color;
	COLORREF m_TextColor;
	CFont *m_Font;
    long m_TextSize;
};


