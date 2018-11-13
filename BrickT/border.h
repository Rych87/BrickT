#pragma once
#include<windows.h>
#include <d2d1.h>

class border
{
public:
	border();
	~border();
	POINT getStartPad();
	POINT st;
	void draw(HDC);
	void draw(ID2D1HwndRenderTarget *);
	int getLeft();
	int getRight();
	int getTop();
	int getBottom();
	int x, y, x1, y1;
};

