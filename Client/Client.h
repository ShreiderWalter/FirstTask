#ifndef CLIENT_H
#define CLIENT_H

#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include <Windows.h>
#include <string>
#include <thread>

/** Available color palette */
#define White RGB(255, 255, 255)
#define Red RGB(255, 0, 0)
#define Blue RGB(0, 0, 255)
#define Orange RGB(255, 140, 0)
#define Green RGB(0, 100, 0)
#define Yellow RGB(255, 255, 0)

/** Error messages*/
#define CONNECTION_FAILED 1
#define CONNECTION_CORRUPTED 2

#define PIPE_NAME TEXT("\\\\.\\pipe\\Pipe")

#define Show(Window) RedrawWindow(Window, 0, 0, 0); ShowWindow(Window, SW_SHOW);


class Client
{
private:
	HANDLE hPipe;
	
	static HWND BCX_Form(char*, int = 0, int = 0, int = 250, int = 150, int = 0, int = 0);

public:
	Client();
	~Client();

	void run();

	int BCX_Circle(HWND, int, int, int, int = 0, int = 0, HDC = 0);
	void LoadForm();

	static HINSTANCE BCX_hInstance;
	static int BCX_ScaleX;
	static int BCX_ScaleY;
	static std::string BCX_ClassName;
	static HWND Form;

	static int picked_color;
	static int failed_error;

};

#endif //CLIENT_H