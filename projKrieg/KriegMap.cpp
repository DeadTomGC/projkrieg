#include "KriegMap.h"
#include <windows.h>
#include <fstream>
#include <iostream>




int KriegMap::loadMapFromFile(const std::string& filename){

	if (!Sprite::getDefaultRenderer()){
		std::cerr << "Warning! renderer is NULL!" << std::endl;
	}

	const int buffSize = 256;
	char line[buffSize];
	int i = 0;
	std::ifstream mapfile(filename);
	mapfile.getline(line, buffSize);
	HINSTANCE hGetProcIDDLL = LoadLibrary(line);
	if (!hGetProcIDDLL) {
		std::cerr << "could not load the dynamic library" << std::endl;
		return -1;
	}

	getObject = (f_factory)GetProcAddress(hGetProcIDDLL, "getObject");
	if (!getObject) {
		std::cerr << "could not locate the function getObject" << std::endl;
		return -3;
	}
	getObjectByIndex = (f_factory_int)GetProcAddress(hGetProcIDDLL, "getObjectByIndex");
	if (!getObjectByIndex) {
		std::cerr << "could not locate the function getObjectByIndex" << std::endl;
		return -4;
	}
	getFirstObject = (f_factory_f_obj)GetProcAddress(hGetProcIDDLL, "getFirstObject");
	if (!getFirstObject) {
		std::cerr << "could not locate the function getFirstObject" << std::endl;
		return -5;
	}

	getNextObject = (f_factory_n_obj)GetProcAddress(hGetProcIDDLL, "getNextObject");
	if (!getNextObject) {
		std::cerr << "could not locate the function getNextObject" << std::endl;
		return -6;
	}

	getTypeCount = (f_type_count)GetProcAddress(hGetProcIDDLL, "getTypeCount");
	if (!getTypeCount) {
		std::cerr << "could not locate the function getTypeCount" << std::endl;
		return -7;
	}

	setSSD = (f_setSSD)GetProcAddress(hGetProcIDDLL, "setSSD");
	if (!setSSD) {
		std::cerr << "could not locate the function setRenderer" << std::endl;
		return -2;
	}
	//set renderer of the Dll so sprites are rendered to the same location
	setSSD(Sprite::getSSD());

	// read objects into array
	objectCount = getTypeCount();
	objectIndex = new Object*[objectCount];
	Object* temp = getFirstObject();
	if (temp){
		objectIndex[0] = temp;
	}
	else{
		std::cerr << "ERROR: could not locate any Objects " <<std::endl;
	}
	for (int i = 1; i < objectCount; i++){
		objectIndex[i] = getNextObject();
		if (!objectIndex[i]){
			std::cerr << "ERROR: could not locate the object numbered " << i << std::endl;
			return -1;
		}
	}
	Block *leftMost=0;
	Block *current=0;
	Block *tempNew=0;
	int lineNum = 1;
	int colNum = 0, allColNum = 0;
	while (!mapfile.eof()){
		lineNum++;
		mapfile.getline(line, buffSize);
		for (i = 0; line[i] == ' '; i++){}
		if (line[i] == '#'){
			continue;
		}
		if (line[i] == '>'){
			i++;
			if (line[i] == '-'){
				current = new KriegBlock(this);
				leftMost = current;
				current->addToList(visBlocks);
				current->setX(0);
				current->setY(0);
				current->setSizeX(spacingX);
				current->setSizeY(spacingY);
				colNum++;
			}
			else
				if (line[i] == '>'){
					tempNew = new KriegBlock(this);

					tempNew->setX(current->getX() + spacingX);
					tempNew->setY(current->getY());
					tempNew->setSizeX(spacingX);
					tempNew->setSizeY(spacingY);

					current->setRight(tempNew);
					tempNew->setLeft(current);
					if (current->getUp() && current->getUp()->getRight()){
						tempNew->setUp(current->getUp()->getRight());
						current->getUp()->getRight()->setDown(tempNew);
					}
					current = tempNew;
					current->addToList(visBlocks);
					
					colNum++;
				}
				else
					if (line[i] == 'v'){
						tempNew = new KriegBlock(this);
						tempNew->setUp(leftMost);
						leftMost->setDown(tempNew);

						tempNew->setX(leftMost->getX());
						tempNew->setY(leftMost->getY() + spacingY);
						tempNew->setSizeX(spacingX);
						tempNew->setSizeY(spacingY);

						current = tempNew;
						leftMost = current;
						current->addToList(visBlocks);
						if (allColNum == 0){
							allColNum = colNum;
							colNum = 1;
						}
						else if (colNum != allColNum){
							//error case
							std::cerr << "ERROR: inconsistent column counts due to line " << lineNum << std::endl;
							return -1;
						}
						else{
							colNum = 1;
						}
					}
					else{
						//error case
						std::cerr << "ERROR: unexpected symbol on line " << lineNum << std::endl;
						return -1;
					}

					continue;
		}
		int objectType = atoi(line);
		if (objectType>=0 && objectType<objectCount){
			temp = objectIndex[objectType]->new_instance(current);
			current->addObject(temp);
		}
		else{
			//error case
			std::cerr << "ERROR: no such object, line " << lineNum << std::endl;
			return -1;
		}


	}
	return 0;
}

int KriegMap::getInt(char* text, int& start, int end){
	int result = 0;
	for (start = 0; text[start] == ' '; start++){}
	while (start < end && text[start] <= '9' && text[start] >= '0'){
		result = result * 10 + text[start] - '0';
	}
	return result;
}

void KriegMap::update(){
	Block* temp = visBlocks;
	while (temp){
		temp->update();
		temp = temp->getNext();
	}
}