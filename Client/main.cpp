#include "Client.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Client * client;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR CmdLine, int CmdShow)
{
	client = new Client;

	WNDCLASS Wc;
	MSG Msg;
	client->BCX_ClassName = "Draw Circle";
	client->BCX_ScaleX = 1;
	client->BCX_ScaleY = 1;
	client->BCX_hInstance = hInst;
	Wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst;
	Wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	Wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	Wc.lpszMenuName = nullptr;
	Wc.lpszClassName = client->BCX_ClassName.c_str();
	RegisterClass(&Wc);

	client->LoadForm();
	client->run();

	MSG msg = { 0 };
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (Client::picked_color > 0)
			InvalidateRect(client->Form, nullptr, FALSE);

		if (Client::failed_error > 0)
		{
			int messagebox = 0;
			if (Client::failed_error == CONNECTION_FAILED)
			{
				messagebox = MessageBox(nullptr, "Connection failed!", "Error", MB_ICONERROR);
			}
			else if (Client::failed_error == CONNECTION_CORRUPTED)
			{
				messagebox = MessageBox(nullptr, "Connection corrupted!", "Error", MB_ICONERROR);
			}

			if (messagebox > 0)
			{
				switch (messagebox)
				{
				case IDOK:
					UnregisterClass(client->BCX_ClassName.c_str(), client->BCX_hInstance);
					PostQuitMessage(0);
					return 0;
				}
			}
		}
	}

	delete client;
	client = nullptr;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_ACTIVATE:
		break;
	case WM_PAINT:
		if (Client::picked_color < 0)
			Client::picked_color = White;
		client->BCX_Circle(hWnd, 100, 100, 55, Client::picked_color, 1);
		
		break;
	case WM_DESTROY:
		UnregisterClass(client->BCX_ClassName.c_str(), client->BCX_hInstance);
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}