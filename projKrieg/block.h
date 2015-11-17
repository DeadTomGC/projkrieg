#pragma once
#include "core.h"
#include <string>

//Only contains functionality that is not likely to change

class Block{

protected:
	Block *right, *left, *up, *down,*next,*prev;
	Object* first;
	int x, y;
	int sizeX, sizeY;
	Map* map;
	bool upToDate,active;
public:
	Block(Map* map){
		this->map = map;
	}
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
	int getX(){ return x; }
	void setX(int x){ this->x = x; }
	int getY(){ return y; }
	void setY(int y){ this->y = y; }
	int getSizeX(){ return sizeX; }
	void setSizeX(int sizeX){ this->sizeX = sizeX; }
	int getSizeY(){ return sizeY; }
	void setSizeY(int sizeY){ this->sizeY = sizeY; }
	Map* getMap(){ return map; }
	void setMap(Map* map){ this->map = map; }
	Object* getFirstObject(){ return first; }
	
	virtual void deActivateAndHide() = 0;
	virtual void activateAndShow() = 0;
	virtual void addObject(Object* object) = 0;
	virtual void update()=0;
	virtual void checkView()=0;
	virtual void seekView()=0;
	virtual void addToList(Block* &firstInList)=0;
};
