#pragma once
#include "CMyColorButton.h"



struct PropertyPageOption:	CPropertyPageImpl<PropertyPageOption>,
							CWinDataExchange<PropertyPageOption>
{
	enum {IDD = IDD_PROPPAGE_CAPTION};
	PropertyPageOption();
	~PropertyPageOption();
	BEGIN_MSG_MAP(PropertyPageOption)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_PAINT,OnPaint)
		MESSAGE_HANDLER(WM_COLOR_CHANGE,OnColorChange)
		COMMAND_HANDLER(IDC_LINESIZE,CBN_SELCHANGE,OnSelChange)
		CHAIN_MSG_MAP(CPropertyPageImpl<PropertyPageOption>)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DDX_MAP(PropertyPageOption)
		DDX_CONTROL(IDC_BTN_COLOR,m_ColorButton)
	END_DDX_MAP()

	// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnColorChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	int OnApply();
	void init(COLORREF color, int colorline);
	
	void DrawPaintWindow(int iID, int iPenID, int iLine, COLORREF clColor);//iID 控件，iPenID 画笔类型，iLine 线宽，COLOR 颜色
	
	int iLineSize;
	COLORREF penColor;//画笔颜色
protected:

	int iLine;//线宽
	//方式1，直接连接一个Windows对象
	CComboBox m_ComBox;
	//CContainedWindowT<CComboBox> m_ComBox;
	
	CMyColorButton m_ColorButton;
};

