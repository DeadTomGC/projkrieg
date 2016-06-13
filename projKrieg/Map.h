#pragma once

#include "core.h"
#include <string>

//Only contains functionality that is not likely to change
typedef void(__cdecl *f_setSSD)(SharedSpriteData* ssd);
typedef Object*(__cdecl *f_factory)(std::string& name);
typedef Object*(__cdecl *f_factory_int)(int index);
typedef Object*(__cdecl *f_factory_f_obj)();
typedef Object*(__cdecl *f_factory_n_obj)();
typedef int(__cdecl *f_type_count)();

class Map{

protected:

	Block *visBlocks;
	Object** objectIndex;
	int objectCount;
	double screenOffsetX, screenOffsetY;
	int scrW, scrH;
	int spacingX,spacingY;
	//functions
	f_setSSD setSSD;
	f_factory getObject;
	f_factory_int getObjectByIndex;
	f_factory_f_obj getFirstObject;
	f_factory_n_obj getNextObject;
	f_type_count getTypeCount;

	virtual void relocateBlocks() = 0;
	virtual void checkLoadedBlocks() = 0;
	virtual void runUpdates() = 0;

public:
	//functions
	Map(int spacingX, int spacingY, int scrW, int scrH){
		this->spacingX = spacingX;
		this->spacingY = spacingY;
		this->scrW = scrW;
		this->scrH = scrH;
		screenOffsetX = 0;
		screenOffsetY = 0;
		visBlocks = 0;
		objectIndex = 0;
		setSSD = 0;
		getObject = 0;
		getObjectByIndex = 0;
		getFirstObject = 0;
		getNextObject = 0;
		getTypeCount = 0;
		objectCount = 0;
	}


	virtual int loadMapFromFile(const std::string& filename)=0;
	virtual void update()=0;

	virtual void move(double distPerFrameX, double distPerFrameY) = 0;

	int getScreenW(){ return scrW; }
	int getScreenH(){ return scrH; }
	double getScreenOffsetX(){ return screenOffsetX; }
	double getScreenOffsetY(){ return screenOffsetY; }
	void setScreenOffset(double screenOffsetX, double screenOffsetY){ this->screenOffsetX = screenOffsetX; this->screenOffsetY = screenOffsetY; }
	
	Block* getVisBlocks(){ return visBlocks; }
	void setVisBlocks(Block* visBlocks){ this->visBlocks = visBlocks; }

};