#pragma once
#include "SDL.h"

using namespace std;

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void UpdateListener(SDL_Event *appEvent) = 0;
};