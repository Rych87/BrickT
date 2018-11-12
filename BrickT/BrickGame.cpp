#include "BrickGame.h"

BrickGame::BrickGame(ID2D1HwndRenderTarget * _pRT)
{
	_DeltaTime=0;
	PadInst.set((bord.x1-bord.x)/2, (bord.y1-bord.y));
	rych.setPos((PadInst.GetLeftX()+PadInst.GetRightX())/2, PadInst.GetY()-1-rych.GetRad());
	_MouseXpos=(PadInst.GetLeftX()+PadInst.GetRightX())/2;
	rych.isStick=true;
		//D2D

	pRT=_pRT;
}

BrickGame::~BrickGame()
{
}

void BrickGame::Update(float DeltaTime)
{
	_DeltaTime=DeltaTime;
	float DeltaY, DeltaPad, DeltaX;
	int MaxDelta;
	//привязка к pad



	//Проверка движущихся объектов

	DeltaX=fabs(rych.GetXspeed())*DeltaTime;			//Перемещение по X и Y за DeltaTime;
	DeltaY=fabs(rych.GetYspeed())*DeltaTime;			//
	DeltaPad=fabs(PadInst.GetSpeed())*DeltaTime;		//Перемещение платформы	
	
	if(DeltaX>DeltaY)
		MaxDelta=(int)DeltaX;
	else
		MaxDelta=(int)DeltaY;

	MaxDelta+=1;

	for (int i = 1; i <= MaxDelta; ++i){
		rych.UpdatePosition(MaxDelta, DeltaTime);
		PadInst.SetSpeed((_MouseXpos-PadInst.GetMidX())*2);
		PadInst.UpdatePosition(MaxDelta, DeltaTime, bord.x, bord.x1);
		if (rych.isStick) {
			rych.Stick(PadInst.GetSpeed(), PadInst.GetY());
		}
	


		//bricks

		switch (r1.check(rych.GetX(), rych.GetY(), rych.GetRad())){
		case 0:
			break;
		case 1:		//hit sides
			rych.ReverseX();
			break;
		case 2:		//hit top/bottom
			rych.ReverseY();
			break;
					//hit corners
		case 3:	
			//rych.SetXspeed(-abs(rych.GetXspeed()));							//top left
			//rych.SetYspeed(-abs(rych.GetYspeed()));
			rych.Set_xS_neg();
			rych.Set_yS_neg();
			break;
		case 4:
			//rych.SetXspeed(abs(rych.GetXspeed()));							//top right
			//rych.SetYspeed(-abs(rych.GetYspeed()));
			rych.Set_xS_pos();
			rych.Set_yS_neg();
			break;
		case 5:
			//rych.SetXspeed(-abs(rych.GetXspeed()));							//bottom left
			//rych.SetYspeed(abs(rych.GetYspeed()));
			rych.Set_xS_neg();
			rych.Set_yS_pos();
			break;
		case 6:
			//rych.SetXspeed(abs(rych.GetXspeed()));							//bottom right
			//rych.SetYspeed(abs(rych.GetYspeed()));
			rych.Set_xS_pos();
			rych.Set_yS_pos();
			break;
		case 7:		//hitlast
			rych.ReverseX();
			rych.ReverseY();
			break;
		}

		// pad
		if (rych.GetY() + rych.GetRad() >= PadInst.GetY() && rych.GetX() >= PadInst.GetLeftX() && rych.GetX() <= PadInst.GetRightX()){
			//if(abs((abs(rych.GetXspeed())+(abs(PadInst.GetSpeed())/4))/rych.GetFullSpeed()) <=0.866)
				rych.SetXspeed(rych.GetXspeed()+PadInst.GetSpeed()/4);
			//else
				//rych.SetXspeed(rych.GetFullSpeed()*0.866*rych.GetXspeed()/abs(rych.GetXspeed()));

			//rych.ySpeed();

			rych.ReverseY();
		}


		// border

		if (rych.GetX()-rych.GetRad() < bord.x + 1 && rych.GetXspeed() < 0)
			rych.ReverseX();

		if (rych.GetX()+rych.GetRad() > bord.x1 - 1 && rych.GetXspeed() > 0)
			rych.ReverseX();

		if (rych.GetY() - rych.GetRad() < bord.y + 1 && rych.GetYspeed() < 0)
			rych.ReverseY();

		if (rych.GetY() > bord.y1)
			PostQuitMessage(0);
	}
	//PadInst.SetSpeed((_MouseXpos-PadInst.GetMidX())*2);

}

void BrickGame::Draw()
{
	pRT->BeginDraw();
	pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	bord.draw(pRT);
	rych.draw(pRT);
	PadInst.draw(pRT);
	r1.draw(pRT);
	pRT->EndDraw();
}

float BrickGame::getPadX()
{
	return PadInst.GetMidX();
}

void BrickGame::Input(UINT m_Msg,WPARAM,LPARAM lParam)
{
	switch(m_Msg)
	{
	case WM_MOUSEMOVE:
		_MouseXpos=LOWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		if(rych.isStick){
		rych.isStick=false;
		rych.SetXspeed(PadInst.GetSpeed());
		}
		break;
	}
}