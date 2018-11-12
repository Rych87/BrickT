#pragma once
#include<windows.h>
#include <d2d1.h>

class border
{
public:
	border();
	~border();
	POINT getStartPad();
	int x, y, x1, y1;
	POINT st;
	void draw(HDC);
	void draw(ID2D1HwndRenderTarget *);
};

