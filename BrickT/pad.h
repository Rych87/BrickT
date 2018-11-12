#pragma once
#include<Windows.h>
#include<d2d1.h>

class pad
{
public:
	pad();
	void set(int, int);
	~pad();
	void UpdatePosition(int,float,int,int);
	void SetSpeed(float);
	float GetSpeed();
	void SetA(int);
	void draw(HDC);
	void draw(ID2D1HwndRenderTarget *);   //D2D
	float GetLeftX();
	float GetRightX();
	float GetMidX();
	float GetY();
private:
	float _X, _Y, _S, _A;
	float _MaxS;
	int _L;
	int _H;
};

