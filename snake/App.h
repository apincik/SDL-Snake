#pragma once
#include "SDL.h"
#include "Gui.h"
#include <forward_list>
#include <map>
#include "EntitySnake.h"
#include "IEntity.h"
#include "Map.h"
#include "Subject.h"
#include "Config.h"

using namespace std;

class App
{

public:
	App();
	~App();
	int Run();

	unsigned int GetMapRowCount();
	unsigned int GetMapColCount();

	Config AppConfig;

private:
	SDL_Window *Window;
	SDL_Surface *WindowSurface;
	SDL_Renderer *Renderer;

	Subject ObserverSubject;
	Gui AppGui;
	bool IsRunning = false;
	Map AppMap;
	
	//map<int, forward_list<IEntity*>> MapEntities;
	//forward_list<IEntity*> Entities;

	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGT = 600;
	static const int MAP_CELL_WIDTH = 20;
	static const int MAP_CELL_HEIGHT = 20;

	bool Init();
	void Loop();
	void Render();
	void Free();

	void OnEvent(SDL_Event *event);
};

