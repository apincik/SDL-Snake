#pragma once
#include "SDL.h"
#include "IEntity.h"
#include "IObserver.h"
#include "EDirection.h"
#include<stack>

using namespace std;

class EntitySnake : public IEntity, IObserver
{
public:
	EntitySnake();
	EntitySnake(int snakeIndex);
	void SetPosition(int x, int y);
	SDL_Point GetPosition();
	virtual void Render(SDL_Renderer &renderer);
	virtual void Update(int params[]);
	void UpdateListener(SDL_Event *appEvent);
	int GetIndex();
	EDirection Direction;
	int DirectionCounter = 0;
private:
	void OnDirectionChange(EDirection direction);
	SDL_Point Position;
	int Index;
	stack<EDirection> MoveStack;
};