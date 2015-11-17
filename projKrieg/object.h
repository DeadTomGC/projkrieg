#pragma once
#include "core.h"
#include <string>

//Only contains functionality that is not likely to change

class Object{
public:
	Object* getNext(void){ return next; }
	Object* getPrev(void){ return prev; }
	void setParent(Block* parent){ this->parent = parent; }
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
	Object(Block* parent);

	void hide();
	void show();

	virtual void update(void) = 0;  //override in subclasses
	virtual Object* new_instance(Block* parent) = 0; //override in subclasses
	virtual std::string* getTypeName() = 0;
	static std::string typeName;
protected:
	Object *next, *prev;
	Sprite* first;
	Block* parent;
	Map* map;
};
