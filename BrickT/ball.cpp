#include "ball.h"
#include<math.h>


ball::ball(int R, float x, float y)
{
	_Size = R;
	_X = x;
	_Y = y;
	_xS = 0;
	_yS = 0;
	_S=300;
}

float ball::GetXspeed()
{
	return _xS;
}

float ball::GetYspeed()
{
	return _yS;
}

void ball::SetXspeed(float DS)
{
	if(fabs(DS/_S)>=0.866)
		_xS = _S*0.866*(DS/fabs(DS));
	else if(fabs(DS/_S)<=0.258 && _xS!=0)
		_xS = _S*0.258*(DS/fabs(DS));
	else if (_xS==0)
		_xS = _S*0.258;
	else
		_xS=DS;
	_yS = sqrt(_S*_S - _xS*_xS);
}

void ball::SetYspeed(int S)
{
	_yS=S;
	_xS = sqrt(_S*_S - _yS*_yS);
}

void ball::ReverseX()
{
	_xS=-_xS;
}

void ball::ReverseY()
{
	_yS=-_yS;
}
int ball::GetX()
{
	return (int)_X;
}

int ball::GetY()
{
	return (int)_Y;
}
int ball::GetRad()
{
	return _Size;
}
void ball::draw(HDC hdc)
{
	Ellipse(hdc, _X-_Size, _Y-_Size, _X+_Size, _Y+_Size);
}

void ball::draw(ID2D1HwndRenderTarget * pRT)
{
	ID2D1SolidColorBrush * Brush;
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &Brush);
	pRT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((int)_X,(int)_Y),_Size,_Size), Brush, 1.0, 0);
	Brush->Release();
}

void ball::ySpeed(void)
{
	_yS = sqrt(_S*_S - _xS*_xS);
}

float ball::GetFullSpeed(void)
{
	_S = sqrt((float)(_yS*_yS + _xS*_xS));
	return _S;
}
void ball::UpdatePosition(int Step, float DeltaTime)
{
	_X+=_xS*DeltaTime/Step;
	_Y+=_yS*DeltaTime/Step;
}

void ball::setPos(int x, int y)
{
	_X=x;
	_Y=y;
}
void ball::Stick(int pS,int y)
{
	_yS=0;
	_xS=pS;
	_Y=y-1-_Size;
}
void ball::Set_xS_pos()
{
	_xS=abs(_xS);
}
void ball::Set_xS_neg()
{
	_xS=-abs(_xS);
}
void ball::Set_yS_pos()
{
	_yS=abs(_yS);
}
void ball::Set_yS_neg()
{
	_yS=-abs(_yS);
}