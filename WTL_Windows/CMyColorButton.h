#pragma once
struct CMyColorButton : CWindowImpl<CMyColorButton,CButton>,
						COwnerDraw<CMyColorButton>
{
	CMyColorButton();
	~CMyColorButton();
	BEGIN_MSG_MAP(CMyColorButton)
		REFLECTED_COMMAND_CODE_HANDLER(BN_CLICKED,OnBnClicked)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CMyColorButton>,1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	 
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	void DrawItem(LPDRAWITEMSTRUCT);
	void init(COLORREF color);

	LRESULT OnBnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled);
	COLORREF m_color;
};

