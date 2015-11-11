#pragma once
#include "Sprite.h"
#include "core.h"
#include "SDL.h"
#include <string>


typedef Object*(__stdcall *f_factory)(std::string& name);
typedef Object*(__stdcall *f_factory_int)(int index);
typedef Object*(__stdcall *f_factory_f_obj)();
typedef Object*(__stdcall *f_factory_n_obj)();
typedef int(__stdcall *f_type_count)();

class Map{

protected:

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

public:
	//functions
	
	virtual int loadMapFromFile(std::string& filename)=0;

	virtual int getScreenW(){ return scrW; }
	virtual int getScreenH(){ return scrH; }
	virtual int getScreenOffsetX(){ return screenOffsetX; }
	virtual int getScreenOffsetY(){ return screenOffsetY; }
};