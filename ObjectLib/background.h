#pragma once
#include "objectTypes.h"

class Background :public Object{
public:
	static std::string typeName;
	Background(Block* parent);
	void update(void);
	Object* new_instance(Block* parent){ return new Background(parent); }
	std::string* getTypeName(){ return &typeName; }

	//variables
	Sprite* primary;

};