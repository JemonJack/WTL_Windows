#include "stdafx.h"
#include "resource.h"
#include "ToolsOptionPages.h"

ToolsOptionPages::ToolsOptionPages(_U_STRINGorID title, UINT uStartPage, HWND hWndParent): 
									CPropertySheetImpl<ToolsOptionPages> (title, uStartPage, hWndParent)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	AddPage(pageOne);
	AddPage(pageTwo);
}


ToolsOptionPages::~ToolsOptionPages()
{
}
