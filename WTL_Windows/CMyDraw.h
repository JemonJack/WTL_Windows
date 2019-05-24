#pragma once
#include "Geometry.h"
#include <vector>

//StraightLine
struct CMyDrawStraightLine : Geometry ,Symbol{
	CMyDrawStraightLine() {};
	CMyDrawStraightLine(int colorline, COLORREF color);
	~CMyDrawStraightLine();
	struct LinePoint {

		CPoint begin;
		CPoint end;
	};
	DrawType drawType() { return StraightLine; }
	void draw(CDCHandle dc);
	void addbeginpoint(long x, long y);
	void addmovepoint(long x, long y);
	void addendpoint(long x, long y);
	void serialize(FILE* file);
	void deserialize(FILE* file);
private:
	//std::vector<LinePoint> vecLinePoint;
	LinePoint m_linepoint;
};

//Rectangle
struct CMyDrawRectangle : Geometry ,Symbol{
	CMyDrawRectangle() = default ;
	CMyDrawRectangle(int colorline, COLORREF color);
	~CMyDrawRectangle();
	DrawType drawtype() { return Rectangle; }
	void draw(CDCHandle dc);
	void addbeginpoint(long x, long y);
	void addmovepoint(long x, long y);
	void addendpoint(long x, long y);
	void serialize(FILE* file);
	void deserialize(FILE* file);

};

