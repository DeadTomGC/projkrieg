#include "Sprite.h"
#include "SDL.h"
#include <string>

class UniversialObject{
	UniversialObject *next, *prev;
	std::string type = "Generic";
	void update(void);
	Sprite* first;


};