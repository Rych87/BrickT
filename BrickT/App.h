#pragma once
#include<windows.h>
#include<d2d1.h>
#include"BrickGame.h"
#include "WindowsTimer.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class App 
{
public:
	App(void);
	~App(void);
	void Run();
	void Initialize();

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM);
	RECT rc;
	BrickGame * rych;
	WindowsTimer Timer;
	HWND hwnd;

	//Direct2d

	ID2D1Factory* D2DFactory;
	ID2D1HwndRenderTarget* pRT;
	//ID2D1Bitmap* BmpPtr;
};
