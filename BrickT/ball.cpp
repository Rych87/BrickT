#include "ball.h"
#include<math.h>


ball::ball(int R, float x, float y)
{
	size = R;
	ball::x = x;
	ball::y = y;
	xS = 0;
	yS = 0;
	S=300;
}

float ball::GetXspeed()
{
	return xS;
}

float ball::GetYspeed()
{
	return yS;
}

void ball::SetXspeed(float DS)
{
	if(fabs(DS/S)>=0.866)
		xS = S*0.866*(DS/fabs(DS));
	else if(fabs(DS/S)<=0.258 && xS!=0)
		xS = S*0.258*(DS/fabs(DS));
	else if (xS==0)
		xS = S*0.258;
	else
		xS=DS;
	yS = sqrt(S*S - xS*xS);
}

void ball::SetYspeed(int S)
{
	yS=S;
	xS = sqrt(S*S - yS*yS);
}

void ball::ReverseX()
{
	xS=-xS;
}

void ball::ReverseY()
{
	yS=-yS;
}
int ball::GetX()
{
	return (int)x;
}

int ball::GetY()
{
	return (int)y;
}
int ball::GetRad()
{
	return size;
}
void ball::draw(HDC hdc)
{
	Ellipse(hdc, x-size, y-size, x+size, y+size);
}

void ball::draw(ID2D1HwndRenderTarget * pRT)
{
	ID2D1SolidColorBrush * Brush;
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &Brush);
	pRT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((int)x,(int)y),size,size), Brush, 1.0, 0);
	Brush->Release();
}

/*void ball::ySpeed(void)
{
	yS = sqrt(S*S - xS*xS);
}*/

float ball::GetFullSpeed(void)
{
	S = sqrt((float)(yS*yS + xS*xS));
	return S;
}
void ball::UpdatePosition(int Step, float DeltaTime)
{
	x+=xS*DeltaTime/Step;
	y+=yS*DeltaTime/Step;
}

void ball::setPos(int x, int y)
{
	ball::x=x;
	ball::y=y;
}
void ball::Stick(int pS,int y)
{
	yS=0;
	xS=pS;
	ball::y=y-1-size;
}
void ball::Set_xS_pos()
{
	xS=abs(xS);
}
void ball::Set_xS_neg()
{
	xS=-abs(xS);
}
void ball::Set_yS_pos()
{
	yS=abs(yS);
}
void ball::Set_yS_neg()
{
	yS=-abs(yS);
}