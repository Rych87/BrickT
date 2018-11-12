#pragma once
#include<windows.h>

class WindowsTimer
{
public:
	WindowsTimer(void);
	~WindowsTimer(void);
	void GetCurrTime();
	void GetPrevTime();
	float DeltaTime();
	int Fps();
private:
	SYSTEMTIME CurrTime, PrevTime, FpsTime;
	FILETIME TempTime;					//	��� �������� � �������
	ULARGE_INTEGER PrevT, CurrT;		//
	int FPS, FrameCount;
};
