#include "stdafx.h"
#include "CMyView.h"
#include "TreeViewListCtrl.h"
#include <time.h>

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
		m_tmpGeometry->id = randID();
		vecgeometries.push_back(m_tmpGeometry);
		tree->geo.push_back(m_tmpGeometry);
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
	HTREEITEM hlineRoot,hrecRoot;
	CString msg;
	tree->DeleteAllItems();
	hlineRoot = tree->InsertItem(_T("Line"),TVI_ROOT,TVI_LAST);
	hrecRoot = tree->InsertItem(_T("Rectangle"), TVI_ROOT, TVI_LAST);

	for(std::vector<Geometry*>::iterator p = vecgeometries.begin(), e = vecgeometries.end(); p != e; ++p) {
		Geometry* tmp = (*p);
		int type = tmp->drawType();
		switch(type) {
		case straightLine: {
			CMyDrawStraightLine* line = (CMyDrawStraightLine*)(*p);
			CString msg;
			msg.Format("%d", line->id);
			tree->InsertItem(msg,hlineRoot,TVI_LAST);
			break;
		}
		case rectangle:{}
			break;
		default:
			break;
		}
	}
	tree->Expand(hlineRoot,TVE_EXPAND);
	tree->Expand(hrecRoot, TVE_EXPAND);
}




int CMyView::randID() {
	int id;
	srand((unsigned)time(NULL));
	id = rand();
	return id;
}