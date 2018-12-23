#pragma once
#include "Win32Window.h"

class Game :
	public Win32Window
{
public:
	Game();
	~Game();

	void init();
	void render();
};

