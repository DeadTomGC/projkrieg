#pragma once
#include "Sprite.h"
#include "core.h"
#include "SDL.h"
#include <string>

class Block{

protected:
	Block *right, *left, *up, *down,*next,*prev;
	Object* first;
	int x, y;
	Map* map;
	bool upToDate;
public:
	Block* getRight(){ return right; }
	void setRight(Block* right){ this->right = right; }
	Block* getLeft(){ return left; }
	void setLeft(Block* left){ this->left = left; }
	Block* getUp(){ return up; }
	void setUp(Block* up){ this->up = up; }
	Block* getDown(){ return down; }
	void setDown(Block* down){ this->down = down; }
	Block* getNext(){ return next; }
	void setNext(Block* next){ this->next = next; }
	Block* getPrev(){ return prev; }
	void setPrev(Block* prev){ this->prev = prev; }
	virtual void update()=0;
	virtual void checkView()=0;
	virtual void seekView()=0;
	virtual void addObject(Object* obj)=0;
	virtual void addToList(Block* &firstInList)=0;
};