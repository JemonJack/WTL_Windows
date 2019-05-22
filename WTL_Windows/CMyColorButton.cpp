#include "stdafx.h"
#include "resource.h"
#include "CMyColorButton.h"


CMyColorButton::CMyColorButton()
{
}
void CMyColorButton::init(COLORREF color) {
	m_color = color;
}

CMyColorButton::~CMyColorButton()
{
}

void CMyColorButton::DrawItem(LPDRAWITEMSTRUCT lpdt) {
	CDCHandle dc = lpdt->hDC;
	CDC dcMem;
	dcMem.CreateCompatibleDC(dc);
	if (lpdt->itemState & ODS_FOCUS) {
		dc.FillSolidRect(&lpdt->rcItem,m_color);
	}
	else {
		dc.FillSolidRect(&lpdt->rcItem, m_color);
	}
	if (lpdt->itemState & ODS_SELECTED)	{
		dc.BitBlt(0,0,80,80,dcMem,0,0,SRCCOPY);
	}
	else {
		dc.BitBlt(0, 0, 80, 80, dcMem, 0, 0, SRCCOPY);
	}
	//dc.FillSolidRect(&lpdt->rcItem, m_color);
	dcMem.RestoreDC(-1);
	dc.RestoreDC(-1);
}

LRESULT CMyColorButton::OnBnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dlg.m_cc.rgbResult = m_color;
	if (dlg.DoModal() == IDOK) {
		m_color = dlg.GetColor();
		Invalidate();
		//GetParent().SendMessage(WM_COLOR_CHANGE,0,0);
		HWND fahWnd = GetParent();
		SendMessage(fahWnd,WM_COLOR_CHANGE, m_color, 0);
	}
	return 0;
}
