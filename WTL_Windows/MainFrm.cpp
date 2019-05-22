// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainFrm.h"
#include "CMyFileDialog.h"

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	//UIUpdateMenuBar();
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

	CreateSimpleStatusBar();

	UIAddToolBar(hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	//Create Splitter Window
	const DWORD dSplitterTyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
				dSplitterExTyle = WS_EX_CLIENTEDGE;
	const DWORD dRichEditStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS |
		WS_HSCROLL | WS_VSCROLL | WS_BORDER |ES_READONLY | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE;

	m_VerSplitter.Create(*this, rcDefault, NULL, dSplitterTyle,dSplitterExTyle);
	m_PaneTreeFormat.Create(m_VerSplitter, IDS_TREELIST_HEADER);
	m_TreeList.Create(m_PaneTreeFormat,rcDefault);
	m_PaneTreeFormat.SetClient(m_TreeList);
	m_VerSplitter.SetSplitterPane(SPLIT_PANE_TOP,m_PaneTreeFormat);

	m_HorSplitter.Create(m_VerSplitter, rcDefault, NULL, dSplitterTyle, dSplitterExTyle);
	m_PaneFormat.Create(m_HorSplitter, IDS_LIST_HEADER);
	m_FormatListView.Create(m_PaneFormat, rcDefault);
	m_PaneFormat.SetClient(m_FormatListView);
	m_Cview.Create(m_HorSplitter,rcDefault,NULL,dSplitterTyle,dSplitterExTyle);
	m_hWndClient = m_VerSplitter;
	UpdateLayout();

	m_VerSplitter.m_cxyMin = 150;
	m_VerSplitter.m_cxyBarEdge =5;
	m_VerSplitter.SetSplitterPos(200);
	m_VerSplitter.SetSplitterPane(SPLIT_PANE_BOTTOM, m_HorSplitter);
	m_HorSplitter.m_cxyMin = 150;
	m_HorSplitter.SetSplitterPos(1000);
	//CRect ddd;m_HorSplitter.GetClientRect(ddd);
	m_HorSplitter.m_cxyBarEdge = 5;
	m_HorSplitter.SetSplitterPanes(m_Cview,m_PaneFormat);
	//m_VerSplitter.SetSplitterExtendedStyle(SPLIT_FIXEDBARSIZE);
	//m_HorSplitter.SetSplitterExtendedStyle(SPLIT_FIXEDBARSIZE);
	m_FormatListView.Init();
	m_TreeList.init();

	//else
	iColorLine = 0;
	cOlor = RGB(255, 0, 0);
	
	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;

	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document
	CProgressBarCtrl progressBarCtrl;
	CreateProgressCtrlInStatusBar(progressBarCtrl);
	for (int i = 0; i < 100; i++)
	{
		Sleep(50);
		progressBarCtrl.StepIt();
	}
	progressBarCtrl.DestroyWindow();
	return 0;
}


LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CPropertySheet sheet(_T("About WTL_WIndow"));
	CPropertyPage<IDD_ABOUTBOX> pgAbout;
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;//È¡ÏûApply°´Å¥
	sheet.AddPage(pgAbout);
	sheet.DoModal();
	//CAboutDlg dlg;
	//dlg.DoModal();
	return 0;
}

void CMainFrame::CreateProgressCtrlInStatusBar(CProgressBarCtrl& pRogressBarCtrl) {
	CStatusBarCtrl c_StatusBarCtrl = m_hWndStatusBar;
	LPCTSTR sMsg = _T("Reading Data");
	CRect rc;
	c_StatusBarCtrl.GetRect(0,&rc);
	CClientDC dc(c_StatusBarCtrl);
	CFontHandle hFont = c_StatusBarCtrl.GetFont();
	CFontHandle hOldfont = dc.SelectFont(hFont);
	CSize sizeText;
	dc.GetTextExtent(sMsg,lstrlen(sMsg),&sizeText);
	dc.SelectFont(hOldfont);
	rc.left += sizeText.cx + 10;
	c_StatusBarCtrl.SetText(0, sMsg);
	c_StatusBarCtrl.RedrawWindow();

	pRogressBarCtrl.Create(c_StatusBarCtrl,rc,NULL,WS_CHILD|WS_VISIBLE);
	pRogressBarCtrl.SetRange(0,100);
	pRogressBarCtrl.SetPos(0);
	pRogressBarCtrl.SetStep(5);

}

LRESULT CMainFrame::OnHidePane(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	m_VerSplitter.SetSinglePaneMode(SPLIT_PANE_BOTTOM);
	return 0;
}

LRESULT CMainFrame::OnShowPaneBoard(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	m_VerSplitter.SetSinglePaneMode(SPLIT_PANE_NONE);
	return 0;
}

LRESULT CMainFrame::OnHidePaneBoard(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	m_VerSplitter.SetSinglePaneMode(SPLIT_PANE_BOTTOM);
	return 0;
}

LRESULT CMainFrame::OnToolsOptions(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	m_ToolsSheet = new ToolsOptionPages(_T("Tools Option"), 0);
	m_ToolsSheet->pageOne.init(cOlor,iColorLine);
	if (IDOK == m_ToolsSheet->DoModal()) {
		m_Cview.iLine = m_ToolsSheet->pageOne.iLineSize;
		m_Cview.m_Color = m_ToolsSheet->pageOne.penColor;
		iColorLine = m_ToolsSheet->pageOne.iLineSize;
		cOlor = m_ToolsSheet->pageOne.penColor;
	}
	delete m_ToolsSheet;
	return 0;
}

LRESULT CMainFrame::OnDrawLine(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	//if (m_Cview.m_tmpGeometry != NULL) {
	//	delete m_Cview.m_tmpGeometry;
	//	m_Cview.m_tmpGeometry = NULL;
	//}
	//else {
	//	m_Cview.m_tmpGeometry = new CMyDrawStraightLine;
	//}
	m_Cview.iCheckDrawType = 1;
	UISetCheck(ID_DRAW_LINE,1);
	UISetCheck(ID_DRAW_RECTANGLE, 0);
	return 0;
}
LRESULT CMainFrame::OnDrawRectangle(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	//if (m_Cview.m_tmpGeometry != NULL) {
	//	delete m_Cview.m_tmpGeometry;
	//}
	//else {
	//	m_Cview.m_tmpGeometry = new CMyDrawRectangle;
	//}
	m_Cview.iCheckDrawType = 2;
	UISetCheck(ID_DRAW_LINE, 0);
	UISetCheck(ID_DRAW_RECTANGLE, 1);
	return 0;
}

LRESULT CMainFrame::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	CFileDialog filedlg(FALSE);
	if (IDOK == filedlg.DoModal()) {
		char cfilename[260] = { 0 };
		memcpy(cfilename,filedlg.m_szFileName,260);
		for (std::vector<Geometry*>::iterator it = m_Cview.vecgeometries.begin(); it != m_Cview.vecgeometries.end(); it++) {
			(*it)->serialize(cfilename);
		}
	}
	return 0;
}

LRESULT CMainFrame::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
	CMyFileDialog filedialog(TRUE);
	if (filedialog.DoModal() == IDOK) {
		char cfilename[260] = { 0 };
		memcpy(cfilename, filedialog.m_szFileName, 260);
		FILE* file;
		DrawType type;
		char c;
		fpos_t pos;
		if (file = fopen(cfilename, "rb")) {
			while (!feof(file))
			{
				fread(&type, sizeof(int), 1, file);
				switch (type)
				{
				case straightLine:
					m_Cview.m_tmpGeometry = new CMyDrawStraightLine();
					m_Cview.m_tmpGeometry->deserialize(file);
					Invalidate();
					break;
				default:
					break;
				}
				fgetpos(file, &pos);
				c = fgetc(file);
				if (c != EOF)
					fsetpos(file, &pos);
			}
		}
		fclose(file);
	}
	return 0;
}
