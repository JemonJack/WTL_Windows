#pragma once

typedef CWinTraitsOR<LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER> CListTraits;

struct ListViewCtrl:CWindowImpl<ListViewCtrl,CListViewCtrl,CListTraits>,
					CCustomDraw<ListViewCtrl>
{
	DECLARE_WND_SUPERCLASS(NULL, WC_LISTVIEW)
	ListViewCtrl();
	~ListViewCtrl();

	BEGIN_MSG_MAP(ListViewCtrl)
		MESSAGE_HANDLER(WM_CHANGECBCHAIN,OnChangeCBChain)
		MESSAGE_HANDLER(WM_DRAWCLIPBOARD, OnDrawClipBoard)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP_ALT(CCustomDraw<ListViewCtrl>,1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	
	// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnChangeCBChain(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDrawClipBoard(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void Init();
};

