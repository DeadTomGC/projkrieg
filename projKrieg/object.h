#pragma once
#include "Sprite.h"
#include "classes.h"
#include "SDL.h"
#include <string>


class Object{
public:
	Object* getNext(void){ return next; }
	Object* getPrev(void){ return prev; }
	void update(void){}
	Object* new_instance() {return new Object();} //override in subclasses
	void addToList(Object* &firstInList);
protected:
	Object *next, *prev;
	std::string type = "Generic";
	Sprite* first;
	Block* parent;
	Map* map;
};