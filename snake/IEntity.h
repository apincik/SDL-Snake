#pragma once
#include "SDL.h"

using namespace std;

class IEntity
{
public:
	virtual ~IEntity() {};
	virtual void Render(SDL_Renderer &renderer) = 0;
	virtual void Update(int params[]) = 0;
	virtual SDL_Point GetPosition() = 0;
};