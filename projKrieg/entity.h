#pragma once
#include "core.h"

class Entity{
public:
	Entity(Map* map){
		this->map = map;
		x = y = 0;
		rotation = 0;
		roffestX = roffestY = 0;
		first = NULL;
		firstChild = parent = NULL;
		nearest = NULL;
	}
	
	void moveTo(double x, double y);
	double getX();
	double getY();

protected:
	Map* map;
	double x, y;
	double rotation;
	double roffestX, roffestY;
	Sprite* first;
	Entity* firstChild;
	Entity* parent;
	Block* nearest;


};