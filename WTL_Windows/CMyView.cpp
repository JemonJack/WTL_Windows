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
		addFormatInfo();
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
			msg.Format("(%d,%d)(%d,%d)", line->m_linepoint.begin.x,line->m_linepoint.begin.y,line->m_linepoint.end.x,line->m_linepoint.end.y);
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
void CMyView::addFormatInfo() {
	format->DeleteAllItems();
	int colum = 0;
	int colorline = 1;
	for(std::vector<Geometry*>::iterator p = vecgeometries.begin(), e = vecgeometries.end(); p != e; ++p) {
		Geometry* tmp = (*p);
		int type = tmp->drawType();
		switch(type) {
		case straightLine: {
			CMyDrawStraightLine* line = (CMyDrawStraightLine*)(*p);
			format->InsertItem(colum, _T("Line"));
			CString colorline;
			colorline.Format("%d", line->iLine);
			format->SetItemText(colum, 1, colorline);
			CString color;
			color = ColorToCString(line->m_Color);
			format->SetItemText(colum, 2, color);
			break;
		}
		case rectangle:{}
					   break;
		default:
			break;
		}
		colum++;
	}
	colum = 0;
	format->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	format->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	format->SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

CString CMyView::ColorToCString(COLORREF color) {
	CString value;
	BYTE red = GetRValue(color);
	BYTE green = GetGValue(color);
	BYTE blue = GetBValue(color);
	char chr[4];
	itoa(red, chr, 10);
	char chg[4];
	itoa(green, chg, 10);
	char chb[4];
	itoa(blue, chb, 10);
	value.Format("(%d,%d,%d)", _ttoi(chr), _ttoi(chg), _ttoi(chb));
	return value;
}