#ifndef UNICODE
#define UNICODE
#endif

#include"App.h"

#pragma comment(lib, "d2d1")


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{	
	App Rych;
	Rych.Initialize();
	Rych.Run();
}




