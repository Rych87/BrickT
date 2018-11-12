#pragma once
#include<windows.h>
#include"GameInterface.h"

class Button
{
public:
	Button();
	~Button(void);
	void Draw();
	void OnClick();
	void Setup();
	void Input(HWND,UINT,WPARAM,LPARAM);
private:
	RECT rc;
	GameInterface * GI_ptr;
	wchar_t * Label;
};
