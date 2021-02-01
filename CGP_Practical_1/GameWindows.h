#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "resource.h"


class GameWindows
{
private:
	//	Window handle
	static GameWindows* instance;
	HWND g_hWnd;
	HINSTANCE hInstance;
	//	Window's structure
	WNDCLASS wndClass;
	bool isFullscreen;

	GameWindows();
public:
	int r;
	int g;
	int b;
	int speed;

	static GameWindows* getInstance();
	void createWindow();
	void clearWindow();
	bool gameLoop();
	HWND getHWND();
	void setIsFullscreen(bool isFullScreen);
	bool getIsFullscreen();


};

