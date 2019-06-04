#pragma once
#include "CMyDraw.h"
struct ListViewCtrl;
typedef CWinTraitsOR<TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS> CTreeViewTraits;

struct TreeViewListCtrl: CWindowImpl<TreeViewListCtrl,CTreeViewCtrl,CTreeViewTraits>,
	                     CCustomDraw<TreeViewListCtrl>
{
	DECLARE_WND_SUPERCLASS(NULL,WC_TREEVIEW)
	TreeViewListCtrl();
	~TreeViewListCtrl();
	ListViewCtrl*   format;
	std::vector<Geometry*> geo;

	BEGIN_MSG_MAP(TreeViewListCtrl)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnSelectItem)
		CHAIN_MSG_MAP_ALT(CCustomDraw<TreeViewListCtrl>, 1)	
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()


	// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	void init();
	void showlinedata(LPARAM lParam);
	void showrectangledata(LPARAM lParam);
	void addFormatInfo(int& id);
	CString ColorToCString(COLORREF color);

	LRESULT OnSelectItem(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};

