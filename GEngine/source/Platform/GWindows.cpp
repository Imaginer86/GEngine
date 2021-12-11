//#include "GWindows.h"
//#include "../GEngine.h"
//#include "../Core/Time.h"
//#include "../Render/RenderGL.h"

//#include <iostream>

//WWWin
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN 1            // Исключите редко используемые компоненты из заголовков Windows
//#endif
// Файлы заголовков Windows:
//#include <Windows.h>

//Program program;


//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/*
void GInitProgram(Program *&programPtr)
{
	programPtr = &program;
}
*/

/*
void GUpdateLastTickCount()
{
	program.lastTickCount = Core::GetTickCount();
}
*/


/*
void GUpdateKeys()
{
	if (program.keys[VK_PRIOR])
	{
		RenderGL::getInstance()->MoveCameraQ(100.0f * RenderGL::getInstance()->getMoveScale());
	}
	if (program.keys[VK_NEXT])
	{
		RenderGL::getInstance()->MoveCameraQ(-100.0f * RenderGL::getInstance()->getMoveScale());
	}
	if (program.keys['W'])
	{
		//RenderGL::getInstance()->MoveCameraQ(10.0f * getMoveScale());
		RenderGL::getInstance()->MoveCamera(Vector3f(0.0f, 25.0f * RenderGL::getInstance()->getMoveScale(), 0.0f));
	}
	if (program.keys['S'])
	{
		//RenderGL::getInstance()->MoveCameraQ(-10.0f*getMoveScale());
		RenderGL::getInstance()->MoveCamera(Vector3f(0.0f, -25.0f * RenderGL::getInstance()->getMoveScale(), 0.0f));
	}
	if (program.keys['A'])
	{
		RenderGL::getInstance()->MoveCamera(Vector3f(-25.0f * RenderGL::getInstance()->getMoveScale(), 0.0f, 0.0f));
	}
	if (program.keys['D'])
	{
		RenderGL::getInstance()->MoveCamera(Vector3f(25.0f * RenderGL::getInstance()->getMoveScale(), 0.0f, 0.0f));
	}
	if (program.keys[VK_UP])
	{
		//RenderGL::getInstance()->RotateCamera(Quaternion(1.0f * RenderGL::getInstance()->getRotateScale(), Vector3f(1.0f, 0.0f, 0.0f)));
	}
	if (program.keys[VK_DOWN])
	{
		RenderGL::getInstance()->RotateCamera(Quaternion(-1.0f * RenderGL::getInstance()->getRotateScale(), Vector3f(1.0f, 0.0f, 0.0f)));
	}
	if (program.keys[VK_LEFT])
	{
		RenderGL::getInstance()->RotateCamera(Quaternion(-100.0f * RenderGL::getInstance()->getRotateScale(), Vector3f(0.0f, 1.0f, 0.0f)));
	}
	if (program.keys[VK_RIGHT])
	{
		RenderGL::getInstance()->RotateCamera(Quaternion(1.0f * RenderGL::getInstance()->getRotateScale(), Vector3f(0.0f, 1.0f, 0.0f)));
	}
	if (program.keys[VK_TAB])
	{
		program.keys[VK_TAB] = false;
		program.drawDebugInfo = !program.drawDebugInfo;
	}

	if (program.keys[VK_F1])
	{
		program.keys[VK_F1] = false;
		//TODO RenderGL::getInstance()->killWindow();
		if (RenderGL::getInstance()->swithFullscreen()) program.Draw();
		else program.done = true;
	}
	if (program.keys[VK_SPACE])
	{
		if (program.pause) GUpdateLastTickCount();

		program.keys[VK_SPACE] = false;
		program.pause = !program.pause;
	}
	if (program.keys[VK_ESCAPE])
	{
		program.done = true;
	}
	if (program.keys[VK_ADD])
	{
		program.timeScale += 0.1f;
	}
	if (program.keys[VK_SUBTRACT])
	{
		program.timeScale -= 0.1f;
	}

	if (program.keys['L'])
	{
		RenderGL::getInstance()->SetLight(!RenderGL::getInstance()->GetLight());
		RenderGL::getInstance()->UpdateLight();
		program.keys['L'] = false;
	}
}
*/

/*
int GMain()
{
	if (!program.Init(WndProc))
	{
		std::cerr << "Cannot Init." << std::endl;
		return 1;
	}

	program.Draw();	


	MSG msg;//WWWin
	memset(&msg, 0, sizeof(MSG));
	long long tickCount = 0;
	program.lastTickCount = Core::GetTickCount();//_WIN#32


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
				GUpdateKeys();
				for (size_t i = 0; i < 10; ++i)//temp
					if (!program.pause)
					{
						tickCount = Core::GetTickCount();//WWWin
						DWORD milliseconds = tickCount - static_cast<DWORD>(program.lastTickCount);//_WIN#32
						program.lastTickCount = tickCount;
						float dt = static_cast<float>(milliseconds) / 1000.0f;//slow

						if (program.drawDebugInfo && dt > 0.0f)
							program.FPS = static_cast<size_t>(1.0f / dt);


						if (dt) program.Update(dt*program.timeScale);
					}

				program.Draw();
			}
		}
	}
	return 0;
}
*/

//WWWin
/*
LRESULT CALLBACK WndProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
	{
		if (!HIWORD(wParam))
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
		PostQuitMessage(0);
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
		RenderGL::getInstance()->Resize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	default:
		return DefWindowProc(hWND, message, wParam, lParam);
	}

	return DefWindowProc(hWND, message, wParam, lParam);
}
*/