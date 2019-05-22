#pragma once

struct CMyFileDialog: CFileDialogImpl<CMyFileDialog>
{
	CMyFileDialog(BOOL bOpenFileDialog, _U_STRINGorID szDefExt = 0U, _U_STRINGorID szFileName = 0U, 
				  DWORD dwFlags = OFN_READONLY|OFN_OVERWRITEPROMPT,
				  _U_STRINGorID szFilter = 0U, HWND hWndParent = NULL);
	~CMyFileDialog();
	BEGIN_MSG_MAP(CMyFileDialog)
		CHAIN_MSG_MAP(CFileDialogImpl<CMyFileDialog>)
	END_MSG_MAP()
	
	void OnInitDone(LPOFNOTIFY lpon) {
		GetFileDialogWindow().CenterWindow(lpon->lpOFN->hwndOwner);
	}

protected:
	LPCTSTR PrepFilterString(CString& sFilter);
	CString m_sDefExt, m_sFileName, m_sFilter;
};

