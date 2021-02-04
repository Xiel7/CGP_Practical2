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

	GameWindows();do
public:
	int r;
	int g;
	int b;
	int speed; //why this vars are public and not private you ask? because i am fkin lazy to do getters and setters in a fkin practical

	static GameWindows* getInstance();
	void createWindow();
	void clearWindow();
	bool gameLoop();
	HWND getHWND();
	void setIsFullscreen(bool isFullScreen);
	bool getIsFullscreen();


};

