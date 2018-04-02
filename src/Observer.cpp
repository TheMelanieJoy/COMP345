#include "Observer.h"

void Subject::addObserver(Observer* const& obs) {
	observer = obs;
}

void Subject::notify() {
	observer->update();
}