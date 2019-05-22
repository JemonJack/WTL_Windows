#include "stdafx.h"
#include "TreeViewListCtrl.h"


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
	HWND hwnd = GetParent();
	hwnd = m_hWnd;

}
