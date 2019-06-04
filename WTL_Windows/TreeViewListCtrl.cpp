#include "stdafx.h"
#include "TreeViewListCtrl.h"
#include "CMyDraw.h"
#include "ListViewCtrl.h"

TreeViewListCtrl::TreeViewListCtrl()
{
}


TreeViewListCtrl::~TreeViewListCtrl()
{
}

void TreeViewListCtrl::init() {
	HTREEITEM htrRoot, htrNate1, htrDown;
	htrRoot = InsertItem(_T("ROOT"),TVI_ROOT,TVI_LAST);
	htrNate1 = InsertItem(_T("Nate1"),htrRoot,TVI_LAST);
	htrDown = InsertItem(_T("Down"), htrNate1, TVI_LAST);
}

//BOOL TreeViewListCtrl::PreTranslateMessage(MSG* msg) {
//	if(msg->message == WM_ADD_OBJECT) {
//		DrawType type = (DrawType)msg->wParam;
//		switch(type) {
//		case straightLine:
//			showlinedata(msg->lParam);
//			break;
//		case rectangle:
//			showrectangledata(msg->lParam);
//			break;
//		default:
//			break;
//		}
//		return TRUE;
//	}
//	return FALSE;
//}
//
//LRESULT TreeViewListCtrl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
//	LRESULT result = DefWindowProc();
//
//	return result;
//}
void TreeViewListCtrl::showlinedata(LPARAM lParam) {
	CMyDrawStraightLine* line = (CMyDrawStraightLine*)lParam;
	HTREEITEM hRoot, hTree;
	hRoot = InsertItem(_T("Line"), TVI_ROOT, TVI_LAST);
	CString msg;
	msg.Format("(%d,%d)(%d,%d)", line->m_linepoint.begin.x,line->m_linepoint.begin.y,line->m_linepoint.end.x,line->m_linepoint.end.y);
	hTree = InsertItem(msg,hRoot,TVI_LAST);
	Expand(hRoot, TVE_EXPAND);
}
void TreeViewListCtrl::showrectangledata(LPARAM lParam) {

}

LRESULT TreeViewListCtrl::OnSelectItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled) {
	HTREEITEM item = GetSelectedItem();	
	CString msgID;
	GetItemText(item,msgID);
	int id = _ttoi(msgID);
	addFormatInfo(id);
	return 0;
}

void TreeViewListCtrl::addFormatInfo(int& id) {
	format->DeleteAllItems();
	int colum = 0;
	int colorline = 1;
	for(std::vector<Geometry*>::iterator p = geo.begin(), e = geo.end(); p != e; ++p) {
		Geometry* tmp = (*p);
		if(tmp->id == id) {
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

	}
	colum = 0;
	format->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	format->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	format->SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

CString TreeViewListCtrl::ColorToCString(COLORREF color) {
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
