#pragma once
#include "CMyDraw.h"
struct TreeViewListCtrl;


//在绘图中，每一条线都是一个对象，每一个矩形或者圆都是单独的一个对象
struct CMyView : CWindowImpl<CMyView>,
				 CDoubleBufferImpl<CMyView> {
	DECLARE_WND_CLASS(NULL)
	CMyView();
	~CMyView();
	TreeViewListCtrl* tree;


	BEGIN_MSG_MAP(CMyView)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMyView>)
	END_MSG_MAP()



// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)


	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void DoPaint(CDCHandle dc);

	int iLine;
	COLORREF m_Color;
	std::vector<Geometry*> vecgeometries;
	Geometry* m_tmpGeometry;
	int iCheckDrawType; //=1画线 =2画矩形,默认=0

	void addTreeView();

	int randID();

private:
	BOOL bMouseDown;

};

