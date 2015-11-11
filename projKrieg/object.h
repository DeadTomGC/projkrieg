#pragma once
#include "Sprite.h"
#include "core.h"
#include "SDL.h"
#include <string>


class Object{
public:
	Object* getNext(void){ return next; }
	Object* getPrev(void){ return prev; }
	virtual void update(void) = 0;
	virtual Object* new_instance() = 0; //override in subclasses
	void addToList(Object* &firstInList){
		if (firstInList){
			this->next = firstInList;
			firstInList->prev = this;
			firstInList = this;
		}
		else{
			firstInList = this;
		}
	}
protected:
	Object *next, *prev;
	std::string type;
	Sprite* first;
	Block* parent;
	Map* map;
};