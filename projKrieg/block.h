#pragma once
#include "Sprite.h"
#include "classes.h"
#include "SDL.h"
#include <string>

class Block{
public:
	void update(void);
private:
	Block *right, *left, *up, *down,*next,*prev;
	Object* first;
	int x, y;
	Map* map;
	bool upToDate;
public:
	Block();
	void updateObjects();
	void checkView();
	void seekView();
	Block* getRight(){ return right; }
	void setRight(Block* right){ this->right = right; }
	Block* getLeft(){ return left; }
	void setLeft(Block* left){ this->left = left; }
	Block* getUp(){ return up; }
	void setUp(Block* up){ this->up = up; }
	Block* getDown(){ return down; }
	void setDown(Block* down){ this->down = down; }
	void addObject(Object* obj);
	void addToList(Block* &firstInList);
};