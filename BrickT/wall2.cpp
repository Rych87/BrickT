#include "wall2.h"
#include <math.h>
#include <time.h>


wall2::wall2()
{
	int wl[4][10]={0};
	int i, k;
	begin = NULL;

	srand(time(NULL));
	for (i = 0; i < 10; ++i){
		for (k = 0; k < 4; ++k){
			if (wl[k][i]==0){


				if (begin == NULL){
					begin = new w;
					end = begin;
					begin->m.x = 60;
					begin->m.y = 60;
					begin->hb = rand() % 10;
					begin->ptr = NULL;
				}
				else {
					newPtr = new w;
					end->ptr = newPtr;
					newPtr->m.x = 60 + H * i;
					newPtr->m.y = 60 + H * k;
					newPtr->hb = rand() % 10;
					newPtr->ptr = NULL;
					end = newPtr;
				}
			}
		}
	}
}

void wall2::draw(HDC hdc)
{
	//HBRUSH def=CreateSolidBrush(RGB(255,255,255));
	HBRUSH def=(HBRUSH)GetStockObject(WHITE_BRUSH);
	HBRUSH hb1 = CreateSolidBrush(RGB(0, 162, 232));
	HBRUSH hb2 = CreateSolidBrush(RGB(63, 72, 234));
	curr = begin;
	while (curr != NULL){
		switch (curr->hb){
		case 0:
			SelectObject(hdc, hb1);
			break;
		case 1:
			SelectObject(hdc, hb2);
			break;
		default:
			SelectObject(hdc, def);
			break;
		}
		Rectangle(hdc, curr->m.x, curr->m.y, curr->m.x+H, curr->m.y+H);
		curr = curr->ptr;
	}
	SelectObject(hdc, def);
	DeleteObject(hb1);
	DeleteObject(hb2);
}

void wall2::draw(ID2D1HwndRenderTarget * pRT)
{
	ID2D1SolidColorBrush * Brush;
	ID2D1SolidColorBrush * Brush2;
	ID2D1SolidColorBrush * Brush3;
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &Brush);
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PaleGreen, 1.0f), &Brush2);
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PaleTurquoise, 1.0f), &Brush3);

	curr = begin;
	while (curr != NULL){
		pRT->DrawRectangle(D2D1::RectF(curr->m.x, curr->m.y, curr->m.x+H, curr->m.y+H), Brush, 1.0, 0);
		switch (curr->hb){
		case 0:
			pRT->FillRectangle(D2D1::RectF(curr->m.x, curr->m.y, curr->m.x+H, curr->m.y+H), Brush2);
			break;
		case 1:
			pRT->FillRectangle(D2D1::RectF(curr->m.x, curr->m.y, curr->m.x+H, curr->m.y+H), Brush3);
			break;
		default:
			break;
		}
		curr = curr->ptr;
	}
	Brush->Release();
	Brush2->Release();
	Brush3->Release();
}

int wall2::check(int x, int y, int s)
{
	int m=0;
	curr = begin;
	prev = begin;
	int hit = 0;
	while (hit == 0 && curr != NULL){
		if (x > curr->m.x && x < curr->m.x + H && (y - s == curr->m.y + H || y + s == curr->m.y)){
			hit = 1;
			m = 2;
		}
		if (y > curr->m.y && y < curr->m.y + H && (x - s == curr->m.x + H || x + s == curr->m.x)){
			hit = 1;
			m = 1;
		}
		if (pow((float)(curr->m.x - x), 2) + pow((float)(curr->m.y - y), 2) <= s*s){
			hit = 1;
			m = 3;		//top left
		}
		if (pow((float)(x-(curr->m.x + H)), 2) + pow((float)(curr->m.y - y), 2) <= s*s){
			hit = 1;
			m = 4;		//top right
		}
		if (pow((float)(curr->m.x - x), 2) + pow((float)(y-(curr->m.y + H)), 2) <= s*s){
			hit = 1;
			m = 5;		//bottom  left
		}
		if (pow((float)(curr->m.x+H - x), 2) + pow((float)(curr->m.y+H - y), 2) <= s*s){
			hit = 1;
			m = 6;
		}
		if (hit==1){
			if (curr == begin){
				temp = begin;
				begin = begin->ptr;
				curr = begin;
				delete temp;
			}
			else {
				temp = curr;
				prev->ptr = curr->ptr;
				delete temp;
			}
		}
		prev = curr;
		if (curr != NULL)
			curr = curr->ptr;
		else
			m = 7;
	}
	return m;
}


wall2::~wall2()
{
}
