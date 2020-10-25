#include "GWindows.h"
 
#include "../GEngine.h"

Program program;

void GInitProgram(Program* programPtr)
{
	programPtr = &program;
}

int GMain()
{
	if (!program.Init())
	{
		MessageBox(NULL, L"Cannot Init.", L"ERROR", MB_OK | MB_ICONSTOP);
		return 1;
	}

	program.Draw();	

	MSG msg;//_WIN#32
	memset(&msg, 0, sizeof(MSG));
	DWORD tickCount = 0;//_WIN#32
	program.lastTickCount = GetTickCount();//_WIN#32


	while (!program.done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // ���� �� � ������� �����-������ ���������?
		{
			if (msg.message == WM_QUIT)        // �� ������� ��������� � ������?
			{
				program.done = true;          // ���� ���, done=true
			}
			else              // ���� ���, ������������ ���������
			{
				TranslateMessage(&msg);        // ��������� ���������
				DispatchMessage(&msg);        // �������� ���������
			}
		}
		else
		{
			if (program.active)          // ������� �� ���������?
			{
				program.UpdateKeys();
				// �� ����� ��� ������, ������� �����.

				//for (int i = 0; i < 10; ++i)//temp
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:            // �������� ��������� ���������� ����
	{
		if (!HIWORD(wParam))//_WIN#32 // ��������� ��������� �����������
		{
			program.active = true;          // ��������� �������
		}
		else
		{
			program.active = false;          // ��������� ������ �� �������
		}

		return 0;            // ������������ � ���� ��������� ���������
	}
	case WM_SYSCOMMAND:            // ������������� ��������� �������
	{
		switch (wParam)            // ������������� ��������� �����
		{
		case SC_SCREENSAVE:        // �������� �� ���������� �����������?
		case SC_MONITORPOWER:        // �������� �� ������� ������� � ����� ���������� �������?
			return 0;          // ������������� ���
		}
		break;              // �����
	}
	case WM_CLOSE:              // �� �������� ��������� � ��������?
	{
		PostQuitMessage(0);//_WIN#32          // ��������� ��������� � ������
		return 0;            // ��������� �����
	}
	case WM_KEYDOWN:            // ���� �� ������ ������?
	{
		program.keys[wParam] = true;          // ���� ���, �� ����������� ���� ������ true
		return 0;            // ������������
	}
	case WM_KEYUP:              // ���� �� �������� �������?
	{
		program.keys[wParam] = false;          //  ���� ���, �� ����������� ���� ������ false
		return 0;            // ������������
	}
	case WM_SIZE:              // �������� ������� OpenGL ����
	{
		//render->resize(LOWORD(lParam), HIWORD(lParam));//_WIN#32  // ������� �����=Width, ������� �����=Height
		return 0;            // ������������
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);//_WIN#32
}