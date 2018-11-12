#include "pad.h"
#include<math.h>


pad::pad()
{
	_X = 0;
	_Y = 0;
	_S = 50;
	_A = 0;
	_MaxS = 350;
	_L=70;
	_H=5;
}


pad::~pad()
{
}

float pad::GetSpeed()
{
	return _S;
}
void pad::UpdatePosition(int Step, float DeltaTime,int left, int right)
{
	//SetSpeed(_S+_A);
	if((_X>=left+1 && _S<=0) || (_X+_L <=right-1 && _S>=0))
		_X+=_S*DeltaTime/Step;
	else
		_S=0;
}
void pad::SetA(int x)
{
	float diff=x-_X;
	_A=(x-_X+_L/2)/10;
}
void pad::draw(HDC hdc)

{
	Rectangle(hdc, _X, _Y, _X+_L, _Y+_H);
}

void pad::set(int x, int y)
{
	_X = x-_L/2;
	_Y = y;
}


void pad::SetSpeed(float speed)
{
	if (speed <= _MaxS && speed>=-_MaxS)
		_S = speed;
	else if (speed>_MaxS)
		_S = _MaxS;
	else
		_S = -_MaxS;
}

float pad::GetLeftX()
{
	return _X;
}

float pad::GetRightX()
{
	return _X+_L;
}

float pad::GetY()
{
	return _Y;
}

float pad::GetMidX(void)
{
	return _X+_L/2;
}

void pad::draw(ID2D1HwndRenderTarget * pRT)
{
	ID2D1SolidColorBrush * Brush;
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &Brush);
	pRT->DrawRectangle(D2D1::RectF(_X, _Y, _X+_L, _Y+_H), Brush, 1.0, 0);
	Brush->Release();
}