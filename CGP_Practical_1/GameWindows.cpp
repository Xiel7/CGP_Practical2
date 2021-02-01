#include "GameWindows.h"

GameWindows* GameWindows::instance = 0;

GameWindows* GameWindows::getInstance()
{
	if (!instance)
	{
		instance = new GameWindows;
	}

	return instance;
}

GameWindows::GameWindows()
{	
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->speed = 1;
	this->isFullscreen = false;
	this->hInstance = GetModuleHandle(NULL);
	this->g_hWnd = NULL;
}


//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	GameWindows* gWin = gWin->getInstance();

	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//std::cout << wParam << std::endl;
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			break;
		}
		else if (wParam == 70)
		{
			
			if (!gWin->getIsFullscreen())
			{
				gWin->setIsFullscreen(true);
			}
			else if(gWin->getIsFullscreen())
			{
				gWin->setIsFullscreen(false);
			}
		}
		else if (wParam == 82 || wParam == 71 || wParam == 66 || wParam == 38 || wParam == 40)
		{
			if (wParam == 82)
			{
				
				gWin->r += gWin->speed;
				if (gWin->r > 256)
				{
					gWin->r = 0;
				}
			}
			else if (wParam == 71)
			{
				gWin->g += gWin->speed;
				if (gWin->g > 256)
				{
					gWin->g = 0;
				}
			}
			else if (wParam == 66)
			{
				gWin->b += gWin->speed;
				if (gWin->b > 256)
				{
					gWin->b = 0;
				}
			}
			else if (wParam == 38)
			{
				if (!(gWin->speed >= 10))
				{
					gWin->speed += 1;
				}
			}
			else if (wParam == 40)
			{
				if (!(gWin->speed <= 1))
				{
					gWin->speed -= 1;
				}
			}
			

			std::cout << "Press [F] to toggle fullscreen || SPEED : ( " << gWin->speed << ") RGB ( " << "R : " << (int)gWin->r << ", G : " << (int)gWin->g << ", B : " << (int)gWin->b << " ) " << std::endl;
		}



		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameWindows::createWindow()
{
	/*
	Step 1
	Define and Register a Window.
*/

//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACKONWHITE);
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(RIN_CURSOR));
	//wndClass.hCursor = LoadCursorFromFile(AOT);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, 500, 300, g_hWnd, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	//	ShowCursor(false);

}



void GameWindows::clearWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool GameWindows::gameLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/

	/*
		The if- version process one message per one iteration loop
		The while- version will clear the message queue before dealing with your own code.

		Another function is GetMessage.
		This function is not suitable for game, because it will block your program until it recieves a message.
		your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
		Suitable for event based program, such as bussiness app.
	*/
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
		{
			break;
		}
		
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
		
	}

	/*
		Write your code here...
	*/


	return msg.message != WM_QUIT;
}

HWND GameWindows::getHWND()
{
	return this->g_hWnd;
}


void GameWindows::setIsFullscreen(bool con)
{
	isFullscreen = con;
}

bool GameWindows::getIsFullscreen()
{
	return this->isFullscreen;
}
