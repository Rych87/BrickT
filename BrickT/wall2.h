#pragma once
#include<windows.h>
#include<d2d1.h>

class wall2
{
public:
	wall2();
	~wall2();
	struct w {
		POINT m;
		w * ptr; int hb;
	};
	void draw(HDC);
	void draw(ID2D1HwndRenderTarget *);
	int check(int, int, int);
	w * begin;
	w * prev;
	w * next;
	w * curr;
	w * newPtr;
	w * end;
	w * temp;
	const static int H = 40;
};

