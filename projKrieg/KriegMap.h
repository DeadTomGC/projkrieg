#pragma once
#include "core.h"
#include "KriegClasses.h"

class KriegMap : public Map{

protected:
	int getInt(char* text, int& start, int end);

public:
	KriegMap(int spacingX, int spacingY, int scrW, int scrH){
		this->spacingX = spacingX;
		this->spacingY = spacingY;
		this->scrW = scrW;
		this->scrH = scrH;
		VisBlocks = 0;
		objectIndex = 0;
		getObject = 0;
		getObjectByIndex = 0;
		getFirstObject = 0;
		getNextObject = 0;
		getTypeCount = 0;
		objectCount = 0;
	}

	virtual int loadMapFromFile(std::string& filename);

};