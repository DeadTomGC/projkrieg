#pragma once
#include "core.h"
#include "KriegClasses.h"

class KriegBlock : public Block{

public:
	KriegBlock();
	virtual void update();
	virtual void checkView();
	virtual void seekView();
	virtual void addObject(Object* obj);
	virtual void addToList(Block* &firstInList);

};