#pragma once
#include<Windows.h>
#include<d2d1.h>
#include"ball.h"
#include"border.h"
#include"pad.h"
#include"wall2.h"

class BrickGame 
{
public:
	BrickGame(ID2D1HwndRenderTarget *);
	~BrickGame(void);
	void Update(float);
	void Draw();
	void Input(UINT, WPARAM, LPARAM);   //получает координату указателя мыши или сенсора
	float getPadX();
private:
	ball rych;
	border bord;
	pad PadInst;
	wall2 r1;
	HBITMAP buff;
	float _DeltaTime;
	int _MouseXpos;

		//Direct2d
	
	ID2D1HwndRenderTarget* pRT;
};
