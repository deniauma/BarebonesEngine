#pragma once
#include "Win32Window.h"

class BBwindow :
	public Win32Window
{
public:
	BBwindow();
	~BBwindow();

	void init();
	void render();
};

