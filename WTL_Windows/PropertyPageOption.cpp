#include "stdafx.h"
#include "resource.h"
#include "PropertyPageOption.h"


PropertyPageOption::PropertyPageOption():iLine(0),penColor(RGB(255,0,0)),iLineSize(0)
{

	m_psp.dwFlags |= PSP_USEICONID;
	m_psp.pszIcon = MAKEINTRESOURCE(IDI_TABICON);
	m_psp.hInstance = _Module.GetResourceInstance();	
}
void PropertyPageOption::init(COLORREF color,int colorline) {
	if (colorline == 5) {
		iLine = 0;
	}
	else if(colorline == 15) {
		iLine = 1;
	}
	m_ColorButton.init(color);
	penColor = color;
	//m_ComBox未初始化，在InitDialog
	iLineSize = colorline;
}

PropertyPageOption::~PropertyPageOption()
{
}

LRESULT PropertyPageOption::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	DoDataExchange();
	CenterWindow();
	//m_ComBox.SubclassWindow(GetDlgItem(IDC_LINESIZE));
	HWND hWnd = GetDlgItem(IDC_LINESIZE);
	m_ComBox.Attach(hWnd);
	m_ComBox.InsertString(0, _T("正常"));
	m_ComBox.InsertString(1, _T("加粗"));
	m_ComBox.SetCurSel(iLine);
	return 0;
}

int PropertyPageOption::OnApply() {

	return DoDataExchange(true) ? PSNRET_NOERROR : PSNRET_INVALID;
}

LRESULT PropertyPageOption::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	DrawPaintWindow(IDC_SHOW_LINE, PS_SOLID, (10 * iLine + 5), penColor);
	return 0;
}

LRESULT PropertyPageOption::OnSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
	iLine = m_ComBox.GetCurSel();
	iLineSize = (10 * iLine + 5);
	Invalidate();
	return 0;
}

LRESULT PropertyPageOption::OnColorChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bhandled) {
	penColor = (COLORREF)wParam;
	Invalidate();
	return 0;
}

void PropertyPageOption::DrawPaintWindow(int iID, int iPenID,int iLine, COLORREF clColor) {
	CPaintDC pDC(m_hWnd);
	pDC.SaveDC();
	CPen newPen;
	newPen.CreatePen(iPenID, iLine, clColor);
	CRect rect;
	GetDlgItem(iID).GetWindowRect(rect);
	ScreenToClient(rect);
	pDC.SelectPen(newPen);
	pDC.MoveTo(rect.left, rect.bottom + 20);
	pDC.LineTo(rect.right, rect.bottom + 20);
	pDC.RestoreDC(-1);
}