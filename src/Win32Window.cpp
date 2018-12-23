#include "Win32Window.h"
#include <iostream>

#pragma comment (lib, "opengl32.lib")


LRESULT Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
		{
			int width = LOWORD(lParam);  // Macro to get the low-order word.
			int height = HIWORD(lParam); // Macro to get the high-order word.

		}
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

void Win32Window::createWindow()
{
	// Register the window class.
	const char CLASS_NAME[] = "Barebones window";
	bool bQuit = false;

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.style = CS_OWNDC;

	RegisterClass(&wc);

	// Create the window.
	this->hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		"Barebones Engine",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style							
		50, 50, 800, 600,				// Size and position
		NULL,							// Parent window    
		NULL,							// Menu
		GetModuleHandle(NULL),			 // Instance handle
		NULL							// Additional application data
	);

	if (this->hwnd == NULL)
	{
		std::cout << "Error creating the window handle\n" << std::endl;
	}
}

void Win32Window::createGLcontext()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	this->hdc = GetDC(this->hwnd);

	int letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(this->hdc, &pfd);
	SetPixelFormat(this->hdc, letWindowsChooseThisPixelFormat, &pfd);

	this->hglrc = wglCreateContext(this->hdc);
	wglMakeCurrent(this->hdc, this->hglrc);

	ShowWindow(this->hwnd, SW_SHOWDEFAULT);

	//if (!gladLoadGLLoader((GLADloadproc)wglGetProcAddress))
	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

void Win32Window::gameLoop()
{
	bool bQuit = false;
	MSG msg = {};
	while (!bQuit) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}

		this->render();

		SwapBuffers(this->hdc);
	}
}

void Win32Window::destroyGlcontext()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(this->hglrc);
	ReleaseDC(this->hwnd, this->hdc);
	DestroyWindow(this->hwnd);
}

Win32Window::Win32Window()
{
	this->createWindow();
	this->createGLcontext();
	this->init();
	this->gameLoop();
	this->destroyGlcontext();
}


Win32Window::~Win32Window()
{
}

void Win32Window::init()
{
	
}

void Win32Window::render()
{
	
}
