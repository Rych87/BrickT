#include "Menu.h"

Menu::Menu(ID2D1HwndRenderTarget * _pRT, GameInterface * Gptr)
{
	pRT=_pRT;
	X=50;
	GIptr=Gptr;
}

Menu::~Menu(void)
{
}
void Menu::Input(UINT m_Msg,WPARAM,LPARAM)
{
	NewG.SetFunc(GIptr->newGame());
	switch(m_Msg)
	{
	case WM_MOUSEMOVE:
		
		X+=5;
		break;
	case WM_LBUTTONDOWN:
		GIptr->newGame();	
		//X-=5;
		break;
	}
}

void Menu::Draw()
{
	pRT->BeginDraw();
	pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	ID2D1SolidColorBrush * Brush;
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &Brush);
	pRT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(100,100),X,X), Brush, 1.0, 0);
	Brush->Release();
	pRT->EndDraw();
}

void Menu::Update(float x)
{
}