#include "Observer.h"

void Subject::addObserver(Observer* const& observer) {
	observers.push_back(observer);
}

void Subject::notify() {
	for (unsigned int i = 0; i < observers.size(); i++)
		observers[i]->update();
}