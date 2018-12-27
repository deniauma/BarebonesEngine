#pragma once
#include <glad/glad.h>

class Win32Window
{
protected:
	HWND hwnd;
	HDC hdc;
	HGLRC hglrc;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void createWindow();
	void createGLcontext();
	void gameLoop();
	void destroyGlcontext();

public:
	Win32Window();
	~Win32Window();

	void run();
	virtual void init();
	virtual void render();
};

