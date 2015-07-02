#include "Sprite.h"
#include "SDL.h"
#include <string>

class Object{
	Object *next, *prev;
	const std::string type = "Generic";
	void update(void);
	Sprite* first;


};