#include "Subject.h"


void Subject::NotifyObservers(SDL_Event *appEvent)
{
	if (appEvent->type == SDL_WINDOWEVENT) {
		for (auto it : windowListeners) {
			it->UpdateListener(appEvent);
		}
	}
	else if (appEvent->type == SDL_KEYDOWN) {
		for (auto it : keyListeners) {
			it->UpdateListener(appEvent);
		}
	}
}

void Subject::RegisterKeyListener(IObserver *observer)
{
	keyListeners.push_front(observer);
}

void Subject::RegisterWindowListener(IObserver *observer)
{
	windowListeners.push_front(observer);
}

void Subject::UnregisterKeyListener(IObserver *observer)
{
	keyListeners.remove(observer);
}

void Subject::UnregisterWindowListener(IObserver *observer)
{
	windowListeners.remove(observer);
}