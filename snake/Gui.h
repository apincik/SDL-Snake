#pragma once
#include "SDL.h"
#include "IObserver.h"

class Gui : IObserver
{
public:
	Gui();
	Gui(SDL_Window *window);
	void OnWindowShown();
	void OnKeyPress_K();
	void UpdateListener(SDL_Event *appEvent);
private:
	SDL_Window *GuiWindow;
};