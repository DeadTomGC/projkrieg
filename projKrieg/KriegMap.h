#pragma once
#include "core.h"
#include "KriegClasses.h"

class KriegMap : public Map{

protected:
	//helper function
	int getInt(char* text, int& start, int end);
	//relocates all blocks according to the camera
	virtual void relocateBlocks();
	//checks all applicable blocks to see if they should be loaded
	virtual void checkLoadedBlocks();
	//runs all the update methods on blocks
	virtual void runUpdates();

public:
	//initialize params
	KriegMap(int spacingX, int spacingY, int scrW, int scrH) :Map(spacingX, spacingY,scrW,scrH){

	}
	//begin the update process
	virtual void update();
	//load map from file
	virtual int loadMapFromFile(const std::string& filename);
	//move the camera a certain amount perframe (at target framerate) for one real frame
	virtual void move(double distPerFrameX, double distPerFrameY);

};