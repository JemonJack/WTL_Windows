#pragma once
#include "PropertyPageOption.h"

struct ToolsOptionPages: CPropertySheetImpl<ToolsOptionPages>
{
	ToolsOptionPages(_U_STRINGorID title = (LPTSTR)NULL, UINT uStartPage = 0, HWND hWndParent = NULL);
	~ToolsOptionPages();

	BEGIN_MSG_MAP(ToolsOptionPages)
		CHAIN_MSG_MAP(CPropertySheetImpl<ToolsOptionPages>)
	END_MSG_MAP()

	PropertyPageOption pageOne;
	CPropertyPage<IDD_ABOUTBOX> pageTwo;

};

