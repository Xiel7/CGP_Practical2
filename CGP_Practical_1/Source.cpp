//	Ask the compiler to include minimal header files for our program.
#include "GameWindows.h"
#include <d3d9.h>

//	use int main if you want to have a console to print out message
int main()

//	use WinMain if you don't want the console
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWindows* gWin = gWin->getInstance();


	gWin->createWindow();
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 640;
	d3dPP.BackBufferHeight = 480;
	d3dPP.hDeviceWindow = gWin->getHWND();

	IDirect3DDevice9* d3dDevice;
	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWin->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	
	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
		return 0;

	bool executed = gWin->getIsFullscreen();

	while (gWin->gameLoop())//it just works
	{
		//	To Do:
		//	Update.
		
		if (executed != gWin->getIsFullscreen())//this is so that it gets executed once per toggle and not infinitely
		{
			if (gWin->getIsFullscreen())
			{
				d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
				d3dPP.Windowed = false;
				d3dDevice->Reset(&d3dPP);
			}
			else if (!gWin->getIsFullscreen())
			{
				d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
				d3dPP.Windowed = true;
				d3dDevice->Reset(&d3dPP);
			}

			executed = gWin->getIsFullscreen();
		}

		//	Clear the back buffer.
		d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(gWin->r, gWin->g, gWin->b), 1.0f, 0);

		//	Begin the scene
		d3dDevice->BeginScene();
		//	To Do:
		//	Drawing.

		//	End the scene
		d3dDevice->EndScene();

		//	Present the back buffer to screen
		d3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	return 0;
}



//--------------------------------------------------------------------