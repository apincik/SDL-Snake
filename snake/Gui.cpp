#include "Gui.h"

Gui::Gui()
{
}

Gui::Gui(SDL_Window *window)
{
	GuiWindow = window;
}

void Gui::OnWindowShown()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Welcome", "Welcome", GuiWindow);
}

void Gui::OnKeyPress_K()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Welcome", "Welcome", GuiWindow);
}

void Gui::UpdateListener(SDL_Event *appEvent)
{
	if (appEvent->type == SDL_WINDOWEVENT) {
		switch (appEvent->window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			OnWindowShown();
		default:
			break;
		}
	}
	else if (appEvent->type == SDL_KEYDOWN) {
		switch (appEvent->key.keysym.scancode)
		{
		case SDL_SCANCODE_K:
			OnKeyPress_K();
		default:
			break;
		}
	}
}