#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include "App.h"


App::App(void)
{
}

App::~App(void)
{
}

void App::Initialize()
{
	rc.left=20;
	rc.top=20;
	rc.right=540;
	rc.bottom=560;
	
		// Register the window class.
	const wchar_t CLASS_NAME[] = L"BrickT";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);//HINST_THISCOMPONENT;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"RychArc",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		20, 20, 540, 560,

		NULL,       // Parent window    
		NULL,       // Menu
		GetModuleHandle(NULL),//HINST_THISCOMPONENT,  // Instance handle
		NULL       // Additional application data
		);

	//RegisterTouchWindow(hwnd, 1);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	//D2D
	D2DFactory=NULL;
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left,rc.bottom - rc.top);
	hr=D2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
										  D2D1::HwndRenderTargetProperties(hwnd,size),
										  &pRT);
	rych = new BrickGame(pRT);
	SetWindowLongPtrW(hwnd,GWLP_USERDATA,PtrToUlong(rych));
}

void App::Run()
{
	MSG msg;

	while (true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message==WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
			RedrawWindow(hwnd, NULL, NULL, RDW_ERASENOW || RDW_UPDATENOW);
	}
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BrickGame * Ptr;
	HDC hdc;
	static WindowsTimer f;
	if (uMsg == WM_CREATE){
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		Ptr = (BrickGame*)pcs->lpCreateParams;
        SetWindowLongPtrW(hwnd,GWLP_USERDATA,PtrToUlong(Ptr));
		return 0;
    }
    else
    {
        Ptr = reinterpret_cast<BrickGame *>(static_cast<LONG_PTR>(GetWindowLongPtrW(hwnd,GWLP_USERDATA)));

		switch (uMsg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;

			case WM_PAINT:
				Ptr->Draw();
				Ptr->Update(f.DeltaTime());
				return 0;
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MOUSEMOVE:
				Ptr->Input(uMsg,wParam,lParam);

		return 0;

			case WM_ERASEBKGND:
				return (LRESULT)1;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

