#pragma once
#include "core.h"
#include "KriegClasses.h"

class KriegMap : public Map{

protected:
	int getInt(char* text, int& start, int end);

public:
	KriegMap(int spacingX, int spacingY, int scrW, int scrH) :Map(spacingX, spacingY,scrW,scrH){

	}
	virtual void update();
	virtual int loadMapFromFile(const std::string& filename);
	virtual void relocateBlocks();

};