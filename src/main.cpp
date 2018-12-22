#include <glad/glad.h>
#include <iostream>

#pragma comment (lib, "opengl32.lib")

void OnSize(HWND hwnd, UINT flag, int width, int height);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_SIZE:
		{
			int width = LOWORD(lParam);  // Macro to get the low-order word.
			int height = HIWORD(lParam); // Macro to get the high-order word.

										 // Respond to the message:
			OnSize(hwnd, (UINT)wParam, width, height);
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


void OnSize(HWND hwnd, UINT flag, int width, int height)
{
	// Handle resizing
}

int createWindow(int height, int width)
{
	// Register the window class.
	const char CLASS_NAME[] = "Sample Window Class";
	bool bQuit = false;

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.style = CS_OWNDC;

	RegisterClass(&wc);

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Size and position
		0, 0, 800, 600,

		NULL,       // Parent window    
		NULL,       // Menu
		GetModuleHandle(NULL),  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return -1;
	}

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

	HDC ourWindowHandleToDeviceContext = GetDC(hwnd);

	int letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
	SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

	HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
	wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

	ShowWindow(hwnd, SW_SHOWDEFAULT);

	//if (!gladLoadGLLoader((GLADloadproc)wglGetProcAddress))
	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	MSG msg = {};
	/*while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

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

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers(ourWindowHandleToDeviceContext);
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ourOpenGLRenderingContext);
	ReleaseDC(hwnd, ourWindowHandleToDeviceContext);
	DestroyWindow(hwnd);

	return 0;
}

int main()
{
	int res = createWindow(640, 480);

	return res;
}
