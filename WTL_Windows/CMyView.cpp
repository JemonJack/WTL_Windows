#include "stdafx.h"
#include "CMyView.h"



CMyView::CMyView():iLine(0),m_Color(RGB(255,0,0)),bMouseDown(FALSE),iCheckDrawType(0)
{
	m_tmpGeometry = NULL;
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreTranslateMessage(MSG* msg) {
	msg;
	if (msg->message == WM_ADD_OBJECT)
	{
		int a = 0;
	}
	return FALSE;
}

//LRESULT CMyView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
//	CPaintDC pDC(m_hWnd);
//	DoPaint(pDC.m_hDC);
//	return 0;
//}

void CMyView::DoPaint(CDCHandle dc) {
	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect, RGB(255, 255, 255));
	if (m_tmpGeometry != NULL) {
		m_tmpGeometry->draw(dc);
	}
	if (!vecgeometries.empty()) {
		for (std::vector<Geometry*>::iterator it = vecgeometries.begin(); it != vecgeometries.end(); it++) {
			(*it)->draw(dc);
		}
	}
}
LRESULT CMyView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	bMouseDown = TRUE;
	long x = GET_X_LPARAM(lParam);
	long y = GET_Y_LPARAM(lParam);
	switch (iCheckDrawType)
	{
	case 0:
		break;
	case 1:
		m_tmpGeometry = new CMyDrawStraightLine(iLine,m_Color);
		m_tmpGeometry->addbeginpoint(x, y);
		break;
	case 2:
		m_tmpGeometry = new CMyDrawRectangle(iLine, m_Color);
		m_tmpGeometry->addbeginpoint(x, y);
		break;
	default:
		break;
	}

	return 0;
}

LRESULT CMyView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	long x = GET_X_LPARAM(lParam);
	long y = GET_Y_LPARAM(lParam);

	if (m_tmpGeometry != NULL) {
		m_tmpGeometry->addendpoint(x, y);
		vecgeometries.push_back(m_tmpGeometry);
	}
	bMouseDown = FALSE;
	Invalidate();
	return 0;
} 

LRESULT CMyView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	if (bMouseDown) {
		long x = GET_X_LPARAM(lParam);
		long y = GET_Y_LPARAM(lParam);
		if (m_tmpGeometry != NULL) {
			m_tmpGeometry->addmovepoint(x, y);
		}
	}
	Invalidate();
	
	return 0;
}

