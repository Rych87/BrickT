#include "border.h"


border::border()
{
	x = 10;
	y = 10;
	x1 = 510;
	y1 = 520;
	st.x = (x1 - x) / 2;
	st.y = y1 - 8;
}

POINT border::getStartPad(){ return st; }


border::~border()
{
}

void border::draw(HDC hdc)
{
	Rectangle(hdc, x, y, x1, y1);
}

void border::draw(ID2D1HwndRenderTarget * pRT)
{
	ID2D1SolidColorBrush * Brush;
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &Brush);
	pRT->DrawRectangle(D2D1::RectF(x,y,x1,y1), Brush, 1.0, 0);
	Brush->Release();
}