#include "stdafx.h"
#include "CMyView.h"
#include "TreeViewListCtrl.h"
#include "ListViewCtrl.h"

CMyView::CMyView():iLine(0),m_Color(RGB(255,0,0)),bMouseDown(FALSE),iCheckDrawType(0)
{
	m_tmpGeometry = NULL;
}

CMyView::~CMyView()
{
}


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

	long x = GET_X_LPARAM(lParam);
	long y = GET_Y_LPARAM(lParam);
	switch (iCheckDrawType)
	{
	case 0:
		break;
	case 1:
		bMouseDown = TRUE;
		m_tmpGeometry = new CMyDrawStraightLine(iLine,m_Color);
		m_tmpGeometry->addbeginpoint(x, y);
		break;
	case 2:
		bMouseDown = TRUE;
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
	bMouseDown = FALSE;
	if (m_tmpGeometry != NULL) {
		m_tmpGeometry->addendpoint(x, y);
		vecgeometries.push_back(m_tmpGeometry);
		addTreeView();
	}	
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

void CMyView::addTreeView() {
	HTREEITEM hRoot;
	for(std::vector<Geometry*>::iterator p = vecgeometries.begin(), e = vecgeometries.end(); p != e; ++p) {
		Geometry* tmp = (*p);
		int type = tmp->drawType();
		switch(type) {
		case 0:				//line

			break;
		case 1:
			break;
		default:
			break;
		}
	}
	hRoot = tree->InsertItem(_T(""),TVI_ROOT,TVI_LAST);
}
