#include "App.h"
#include "SDL.h"
#include "Gui.h"
#include <iostream>

using namespace std;

int App::Run()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL init error." << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	//App init
	if (!Init()) {
		return EXIT_FAILURE;
	}

	IsRunning = true;
	SDL_Event Event;

	while (IsRunning) {
		while (SDL_PollEvent(&Event) != 0) {
			OnEvent(&Event);
		}

		Loop();
		Render();

		SDL_Delay(20);
	}

	Free();
	return EXIT_SUCCESS;
}

void App::OnEvent(SDL_Event *event)
{
	if (event->type == SDL_QUIT) {
		IsRunning = false;
	}
	
	ObserverSubject.NotifyObservers(event);
}

bool App::Init()
{
	/*
	* Init Window and Renderer
	*/
	if ((Window = SDL_CreateWindow(
		"Snake++",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		App::WINDOW_WIDTH,
		App::WINDOW_HEIGT,
		SDL_WINDOW_SHOWN
	)) == NULL) {
		cout << "Error: unable to create window." << endl;
		return false;
	}

	WindowSurface = SDL_GetWindowSurface(Window);

	if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		cout << "Error: unable to create renderer." << endl;
		return false;
	}

	/*
	* Init GUI
	*/
	AppGui = Gui(Window);
	ObserverSubject.RegisterWindowListener((IObserver*)(&AppGui));

	/*a
	* Init Snake
	*/
	EntitySnake *snakeEntity = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity->SetPosition(260, 250);

	EntitySnake *snakeEntity1 = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity1->SetPosition(250, 250);

	EntitySnake *snakeEntity2 = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity2->SetPosition(240, 250);

	EntitySnake *snakeEntity3 = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity3->SetPosition(230, 250);

	EntitySnake *snakeEntity4 = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity4->SetPosition(220, 250);

	EntitySnake *snakeEntity5 = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity5->SetPosition(210, 250);

	EntitySnake *snakeEntity6 = new EntitySnake(AppConfig.SNAKE_LENGTH++);
	snakeEntity6->SetPosition(200, 250);

	AppMap.Insert(2, 2, snakeEntity);
	AppMap.Insert(2, 2, snakeEntity1);
	AppMap.Insert(2, 2, snakeEntity2);
	AppMap.Insert(2, 2, snakeEntity3);
	AppMap.Insert(2, 2, snakeEntity4);
	AppMap.Insert(2, 2, snakeEntity5);
	AppMap.Insert(2, 2, snakeEntity6);

	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity));
	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity1));
	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity2));
	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity3));
	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity4));
	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity5));
	ObserverSubject.RegisterKeyListener((IObserver*)(snakeEntity6));

	return true;
}

void App::Loop()
{
	forward_list<IEntity*> entities = AppMap.GetAllEntities();
	for (auto it = entities.begin(); it != entities.end(); it++) {
		int params[1];
		(*it)->Update(params);
	}

	AppMap.Update();
}

void App::Render()
{
	SDL_RenderClear(Renderer);

	forward_list<IEntity*> entities = AppMap.GetAllEntities();
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->Render(*Renderer);
	}

	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderPresent(Renderer);
}

void App::Free()
{
	if (Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if (Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	SDL_Quit();
}

App::App()
{
	AppConfig = Config();

	ObserverSubject = Subject();

	AppMap = Map(
		App::WINDOW_WIDTH / App::MAP_CELL_WIDTH,
		App::WINDOW_HEIGT / App::MAP_CELL_HEIGHT
	);
}

App::~App()
{
	if (Window) {
		//?delete Window;
		Window = NULL;
	}

	if (Renderer) {
		//?delete Renderer;
		Renderer = NULL;
	}

	if (WindowSurface) {
		//delete WindowSurface;
		WindowSurface = NULL;
	}

	/*for (unsigned int i = 0; i < App::GetMapRowCount(); i++) {
		delete[] MapEntities[i];
	}

	delete[] MapEntities;
	*/
}

unsigned int App::GetMapRowCount() {
	return App::WINDOW_HEIGT / App::MAP_CELL_HEIGHT;
}

unsigned int App::GetMapColCount() {
	return App::WINDOW_WIDTH / App::MAP_CELL_WIDTH;
}


