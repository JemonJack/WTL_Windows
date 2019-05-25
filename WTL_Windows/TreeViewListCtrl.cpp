#include "stdafx.h"
#include "TreeViewListCtrl.h"
#include "CMyDraw.h"


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
