#include "EntitySnake.h"
#include <queue>
#include<iostream>

using namespace std;

EntitySnake::EntitySnake()
{
	Position = SDL_Point();
	Position.x = 0;
	Position.y = 0;

	Direction = EDirection::DIRECTION_RIGHT;	//Default direction on init
}

EntitySnake::EntitySnake(int snakeIndex) : EntitySnake()
{
	Index = snakeIndex;
}

void EntitySnake::UpdateListener(SDL_Event *appEvent)
{
	if (appEvent->type == SDL_KEYDOWN) {

		switch (appEvent->key.keysym.scancode)
		{
			case SDL_SCANCODE_W:
				OnDirectionChange(EDirection::DIRECTION_UP);
				break;
			case SDL_SCANCODE_S:
				OnDirectionChange(EDirection::DIRECTION_DOWN);
				break;
			case SDL_SCANCODE_A:
				OnDirectionChange(EDirection::DIRECTION_LEFT);
				break;
			case SDL_SCANCODE_D:
				OnDirectionChange(EDirection::DIRECTION_RIGHT);
				break;
			default:
				break;
		}
	}
}

void EntitySnake::OnDirectionChange(EDirection newDirection)
{
	if (
		(newDirection == EDirection::DIRECTION_RIGHT && Direction == EDirection::DIRECTION_LEFT) ||
		(newDirection == EDirection::DIRECTION_LEFT && Direction == EDirection::DIRECTION_RIGHT) ||
		(newDirection == EDirection::DIRECTION_UP && Direction == EDirection::DIRECTION_DOWN) ||
		(newDirection == EDirection::DIRECTION_DOWN && Direction == EDirection::DIRECTION_UP) ||
		(newDirection == Direction)
		) {

		return;
	}

	int offsetMove = 1;

	//cout << "INDEX: " << Index << " directionCount: " << DirectionCounter << endl;

	int moveOffset = DirectionCounter - 1;
	if (Index < DirectionCounter) {
		moveOffset = Index;
	}

	if (Index == 0 && moveOffset > 0) {
		moveOffset = 0;
	}

	/** Copy new moves in front actual **/

	if (moveOffset > 0) {

		queue<EDirection> tempMoveStack;

		tempMoveStack.push(newDirection);
		
		for (int i = 0; i < moveOffset; i++) {
			tempMoveStack.push(Direction);
		}

		while (!MoveStack.empty()) {
			tempMoveStack.push(MoveStack.top());
			MoveStack.pop();
		}

		while (!tempMoveStack.empty()) {
			MoveStack.push(tempMoveStack.front());
			tempMoveStack.pop();
		}
	}
	else if(moveOffset >= -1 && Index != 0) //prevent snake overlap itself, keep same move order
	{

		stack<EDirection> tempMoveStack;

		if (moveOffset > 0) {
			tempMoveStack.push(newDirection);	//store position where entity should go
		}

		for (int i = 0; i < moveOffset; i++) {
			tempMoveStack.push(Direction);
		}

		while (!MoveStack.empty()) {
			tempMoveStack.push(MoveStack.top());
			MoveStack.pop();
		}

		while (!tempMoveStack.empty()) {
			MoveStack.push(tempMoveStack.top());
			tempMoveStack.pop();
		}
	}
	else if (DirectionCounter == 0 && Index == 0 && MoveStack.empty()) //fix when index 0 doesnt do one more move
	{
		MoveStack.push(Direction);
	}



	Direction = newDirection;
	DirectionCounter = 0;
}

void EntitySnake::Update(int params[])
{
	EDirection newDirection;
	
	if (MoveStack.empty()) {
		newDirection = Direction;
	}
	else {
		newDirection = MoveStack.top();
		MoveStack.pop();
	}

	DirectionCounter++;

	switch (newDirection)
	{
		case EDirection::DIRECTION_UP:	//reverted axes ?
			Position.y -= 10;	//(10 + ((Index * 10) * indexPositionBoost));
			break;
		case EDirection::DIRECTION_DOWN:
			Position.y += 10;
			break;
		case EDirection::DIRECTION_LEFT:
			Position.x -= 10;
			break;
		case EDirection::DIRECTION_RIGHT:
			Position.x += 10;
			break;
		default:
			break;
	}

}

void EntitySnake::Render(SDL_Renderer &renderer)
{
	if (Index == 0) {
		SDL_SetRenderDrawColor((SDL_Renderer*)(&renderer), 20, 120, 80, 255);
	}
	else {
		SDL_SetRenderDrawColor((SDL_Renderer*)(&renderer), 125 + Index * 10, 80 - Index * 10, 95 + Index * 5, 255);
	}

	SDL_Rect *rect = new SDL_Rect();
	rect->h = 10;
	rect->w = 10;
	rect->x = Position.x;
	rect->y = Position.y;

	SDL_RenderFillRect((SDL_Renderer*)(&renderer), rect);
}

void EntitySnake::SetPosition(int x, int y)
{
	Position.x = x;
	Position.y = y;
}

SDL_Point EntitySnake::GetPosition()
{
	return Position;
}

int EntitySnake::GetIndex()
{
	return Index;
}
