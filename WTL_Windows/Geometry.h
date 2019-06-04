#pragma once

struct Symbol {
	Symbol();
	int iLine;
	COLORREF m_Color;

};


struct Geometry
{
	Geometry() = default;
	Geometry(int line, COLORREF color) {}
	virtual ~Geometry() {}
	enum DrawType
	{
		StraightLine,
		Rectangle
	};
	virtual DrawType drawType() { return m_Type; }
	virtual void draw(CDCHandle dc) = 0;
	virtual void serialize(FILE* file) = 0;
	virtual void deserialize(FILE* file) = 0;
	virtual void addbeginpoint(long x, long y) = 0;
	virtual void addmovepoint(long x, long y) = 0;
	virtual void addendpoint(long x, long y) = 0;
	int id;
protected:
	DrawType m_Type;
};

