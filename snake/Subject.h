#pragma once
#include<forward_list>
#include "SDL.h"
#include "IObserver.h"

using namespace std;

class Subject
{
public:
	void RegisterWindowListener(IObserver *observer);
	void UnregisterWindowListener(IObserver *observer);
	void RegisterKeyListener(IObserver *observer);
	void UnregisterKeyListener(IObserver *observer);
	void NotifyObservers(SDL_Event *appEvent);
private:
	forward_list<IObserver*> windowListeners;
	forward_list<IObserver*> keyListeners;
};