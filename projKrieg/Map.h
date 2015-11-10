#pragma once
#include "Sprite.h"
#include "classes.h"
#include "SDL.h"
#include <string>


typedef Object*(__stdcall *f_factory)(std::string& name);
typedef Object*(__stdcall *f_factory_int)(int index);
typedef Object*(__stdcall *f_factory_f_obj)();
typedef Object*(__stdcall *f_factory_n_obj)();
typedef int(__stdcall *f_type_count)();

class Map{

private:
	UniversalObject *UniObjs;
	Block *VisBlocks;
	Object** objectIndex;
	int objectCount;
	int screenOffsetX, screenOffsetY;
	int scrW, scrH;
	int spacingX,spacingY;
	//functions
	f_factory getObject;
	f_factory_int getObjectByIndex;
	f_factory_f_obj getFirstObject;
	f_factory_n_obj getNextObject;
	f_type_count getTypeCount;

	int getInt(char* text, int& start, int end);

public:
	//functions
	Map(int spacingX, int spacingY,int scrW,int scrH){
		this->spacingX = spacingX;
		this->spacingY = spacingY;
		this->scrW = scrW;
		this->scrH = scrH;
		UniObjs = 0;
		VisBlocks = 0;
		objectIndex = 0;
		getObject = 0;
		getObjectByIndex = 0;
		getFirstObject = 0;
		getNextObject = 0;
		getTypeCount = 0;
		objectCount = 0;
	}
	int loadMapFromFile(std::string& filename);

	int getScreenW();
	int getScreenH();
	int getScreenOffsetX();
	int getScreenOffsetY();
};