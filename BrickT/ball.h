#pragma once
#include<Windows.h>
#include<d2d1.h>
#include<math.h>


class ball
{
public:
	ball(int=10, float=400, float=150);

	void setPos(int,int);
	void Stick(int, int);
	void Set_xS_pos();
	void Set_xS_neg();
	void Set_yS_pos();
	void Set_yS_neg();

	float GetFullSpeed(void);
	void SetXspeed(float);
	void SetYspeed(int);
	void ReverseX();
	void ReverseY();
	float GetXspeed();
	float GetYspeed();

	int GetX();
	int GetY();
	int GetRad();

	void UpdatePosition(int, float);
	void draw(HDC);
	void draw(ID2D1HwndRenderTarget *);

	//temp

	void ySpeed();
	bool isStick;
private:
	int _Size;
	float _X, _Y;
	int _xS, _yS;
	float _S;
};

