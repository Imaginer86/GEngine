//#include "GWindows.h"
#include "../GEngine.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1            // Исключите редко используемые компоненты из заголовков Windows
#endif
// Файлы заголовков Windows:
#include <Windows.h>

Program program;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


void GInitProgram(Program *&programPtr)
{
	programPtr = &program;
}

void UpdateLastTickCount()
{
	program.lastTickCount = GetTickCount();
}

int GMain()
{
	if (!program.Init(WndProc))
	{
		MessageBox(NULL, "Cannot Init.", "ERROR", MB_OK | MB_ICONSTOP);
		return 1;
	}

	program.Draw();	

	MSG msg;//_WIN#32
	memset(&msg, 0, sizeof(MSG));
	DWORD tickCount = 0;//_WIN#32
	program.lastTickCount = GetTickCount();//_WIN#32


	while (!program.done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				program.done = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (program.active)
			{
				program.UpdateKeys();
				for (int i = 0; i < 10; ++i)//temp
					if (!program.pause)
					{
						tickCount = GetTickCount();//_WIN#32
						DWORD milliseconds = tickCount - program.lastTickCount;//_WIN#32
						program.lastTickCount = tickCount;
						float dt = static_cast<float>(milliseconds) / 1000.0f;//slow

						if (program.drawDebugInfo && dt > 0.0f)
							program.FPS = static_cast<unsigned>(1.0f / dt);


						if (dt) program.Update(dt*program.timeScale);
					}

				program.Draw();
			}
		}
	}
	//delete render;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
	{
		if (!HIWORD(wParam))//_WIN#32 
		{
			program.active = true;
		}
		else
		{
			program.active = false;
		}

		return 0;
	}
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);//_WIN#32
		return 0;
	}
	case WM_KEYDOWN:
	{
		program.keys[wParam] = true;
		return 0;
	}
	case WM_KEYUP:
	{
		program.keys[wParam] = false;
		return 0;
	}
	case WM_SIZE:
	{
		//render->resize(LOWORD(lParam), HIWORD(lParam));//_WIN#32
		return 0;
	}
	default:
		return DefWindowProc(hWND, message, wParam, lParam);//_WIN#32
	}

	return DefWindowProc(hWND, message, wParam, lParam);//_WIN#32
}