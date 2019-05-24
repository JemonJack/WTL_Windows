#include "stdafx.h"
#include "CMyDraw.h"


CMyDrawStraightLine::CMyDrawStraightLine(int colorline, COLORREF color)//子类不能初始化父类的变量？
{
	iLine = colorline;
	m_Color = color;
}


CMyDrawStraightLine::~CMyDrawStraightLine()
{
}
void CMyDrawStraightLine::addbeginpoint(long x, long y) {
	m_linepoint.begin.x = x;
	m_linepoint.begin.y = y;

}
void CMyDrawStraightLine::addmovepoint(long x, long y) {
	m_linepoint.end.x = x;
	m_linepoint.end.y = y;
}
void CMyDrawStraightLine::addendpoint(long x, long y) {
	m_linepoint.end.x = x;
	m_linepoint.end.y = y;
}

void CMyDrawStraightLine::draw(CDCHandle dc) {
	CPen newPen;
	newPen.CreatePen(PS_SOLID, iLine, m_Color);
	HPEN oldPen = dc.SelectPen(newPen);
	dc.MoveTo(m_linepoint.begin);
	dc.LineTo(m_linepoint.end);
	dc.SelectPen(oldPen);
	
}

void CMyDrawStraightLine::serialize(FILE* file) {
	m_Type = drawType();
	fwrite(&m_Type, sizeof(DrawType), 1, file);
	fwrite(&m_Color, sizeof(COLORREF), 1, file);
	fwrite(&iLine, sizeof(int), 1, file);
	fwrite(&m_linepoint, sizeof(LinePoint), 1, file);
}
void CMyDrawStraightLine::deserialize(FILE* file) {
	int ret;
	ret = fread(&m_Color, sizeof(COLORREF), 1, file);
	ret = fread(&iLine, sizeof(int), 1, file);
	ret = fread(&m_linepoint, sizeof(LinePoint), 1, file);
}

CMyDrawRectangle::CMyDrawRectangle(int colorline, COLORREF color) {
	iLine = colorline;
	m_Color = color;

}
CMyDrawRectangle::~CMyDrawRectangle() {

}

void CMyDrawRectangle::draw(CDCHandle dc) {

}
void CMyDrawRectangle::addbeginpoint(long x, long y) {

}
void CMyDrawRectangle::addmovepoint(long x, long y) {

}
void CMyDrawRectangle::addendpoint(long x, long y) {

}
void CMyDrawRectangle::serialize(FILE* file) {

}
void CMyDrawRectangle::deserialize(FILE* file) {

}