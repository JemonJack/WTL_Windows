#include "stdafx.h"
#include "CMyFileDialog.h"


CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, _U_STRINGorID szDefExt, _U_STRINGorID szFileName, 
							 DWORD dwFlags, _U_STRINGorID szFilter, HWND hwndParent):CFileDialogImpl<CMyFileDialog>(
								 bOpenFileDialog, NULL, NULL, dwFlags, NULL, hwndParent),m_sDefExt(szDefExt.m_lpstr),
								m_sFileName(szFileName.m_lpstr),m_sFilter(szFilter.m_lpstr)
{
	m_ofn.lpstrDefExt = m_sDefExt;
	m_ofn.lpstrFilter = PrepFilterString(m_sFilter);
	if (!m_sFileName.IsEmpty()) {
		lstrcpyn(m_szFileName,m_sFileName,_MAX_PATH);
	}
}


CMyFileDialog::~CMyFileDialog()
{
}

LPCTSTR CMyFileDialog::PrepFilterString(CString& sFilter) {
	LPTSTR psz = sFilter.GetBuffer(0);
	LPCTSTR pszRet = psz;
	while ('\0' != *psz){
		if ('|' == *psz) {
			*psz++ = '\0';
		}
		else {
			psz = CharNext(psz);
		}
	}
	return pszRet;
}