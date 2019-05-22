#include "stdafx.h"
#include "ListViewCtrl.h"
#include "Geometry.h"
#include <vector>

ListViewCtrl::ListViewCtrl()
{
}


ListViewCtrl::~ListViewCtrl()
{
}

LRESULT ListViewCtrl::OnChangeCBChain(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

LRESULT ListViewCtrl::OnDrawClipBoard(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

LRESULT ListViewCtrl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

void ListViewCtrl::Init() {
	SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 0, 0);
	InsertColumn(1, _T("ColorLine"), LVCFMT_LEFT,0, 1);
	InsertColumn(2, _T("Color"), LVCFMT_LEFT,0, 2);
	InsertItem(0,_T("Jack"));
	SetItemText(0, 1, _T("123"));
	SetItemText(0, 2, _T("98563"));
	//InsertItem(1, _T("Rose"));
	//SetItemText(1,1,_T("Hi"));
	//SetItemText(1, 2, _T("321"));
	//InsertItem(2, _T("Li"));
	//SetItemText(2, 1, _T("Hehe"));
	//SetItemText(2, 2, _T("112"));

	SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}
LRESULT ListViewCtrl::OnAddObject(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	Geometry* tmpGeometry = (Geometry*)wParam;
	switch (tmpGeometry->drawType())
	{
	case 0://Ö±Ïß

		break;
	case 1://¾ØÐÎ
		break;
	default:
		break;
	}
	return 0;
}
