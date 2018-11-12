#include "WindowsTimer.h"

WindowsTimer::WindowsTimer(void)
{
	GetSystemTime(&CurrTime);
	SystemTimeToFileTime(&CurrTime, &TempTime);
	CurrT.LowPart=TempTime.dwLowDateTime;
	CurrT.HighPart=TempTime.dwHighDateTime;
	FPS=0;
	FrameCount=0;
}

WindowsTimer::~WindowsTimer(void)
{
}

void WindowsTimer::GetCurrTime()
{
	PrevT.LowPart=CurrT.LowPart;
	PrevT.HighPart=CurrT.HighPart;

	GetSystemTime(&CurrTime);
	SystemTimeToFileTime(&CurrTime, &TempTime);
	CurrT.LowPart=TempTime.dwLowDateTime;
	CurrT.HighPart=TempTime.dwHighDateTime;
}

float WindowsTimer::DeltaTime()
{
	GetCurrTime();
	++FrameCount;
	return ((float)(CurrT.QuadPart-PrevT.QuadPart)/10000000);
}

int WindowsTimer::Fps()
{
	if(!CurrT.QuadPart%10000000)
		FPS=FrameCount;
	return FPS;
}
