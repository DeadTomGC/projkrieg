#include "Map.h"
#include <windows.h>
#include <fstream>
#include <iostream>



int Map::loadMapFromFile(std::string& filename){
	const int buffSize = 256;
	char line[buffSize];
	int i = 0;
	std::ifstream mapfile(filename);
	mapfile.getline(line, buffSize);
	HINSTANCE hGetProcIDDLL = LoadLibrary(line);
	if (!hGetProcIDDLL) {
		std::cerr<< "could not load the dynamic library" << std::endl;
		return -1;
	}
	getObject = (f_factory)GetProcAddress(hGetProcIDDLL, "getObject");
	if (!getObject) {
		std::cerr << "could not locate the function getObject" << std::endl;
		return -2;
	}
	getObjectByIndex = (f_factory_int)GetProcAddress(hGetProcIDDLL, "getObjectByIndex");
	if (!getObject) {
		std::cerr << "could not locate the function getObjectByIndex" << std::endl;
		return -3;
	}
	getFirstObject = (f_factory_f_obj)GetProcAddress(hGetProcIDDLL, "getFirstObject");
	if (!getObject) {
		std::cerr << "could not locate the function getFirstObject" << std::endl;
		return -4;
	}

	getNextObject = (f_factory_n_obj)GetProcAddress(hGetProcIDDLL, "getNextObject");
	if (!getObject) {
		std::cerr << "could not locate the function getNextObject" << std::endl;
		return -5;
	}

	getTypeCount = (f_type_count)GetProcAddress(hGetProcIDDLL, "getTypeCount");
	if (!getObject) {
		std::cerr << "could not locate the function getTypeCount" << std::endl;
		return -6;
	}

	// read objects into array
	objectCount = getTypeCount();
	objectIndex = new Object*[objectCount];
	Object* temp = getFirstObject();
	for (int i = 0; i < objectCount; i++){
		objectIndex[i] = getNextObject();
		if (!objectIndex[i]){
			std::cerr << "ERROR: could not locate the object numbered " <<i<< std::endl;
			return -1;
		}
	}
	Block *leftMost;
	Block *current;
	Block *tempNew;
	int lineNum = 1;
	int colNum = 0, allColNum = 0;
	while (!mapfile.end){
		lineNum++;
		mapfile.getline(line, buffSize);
		for (i = 0; line[i] == ' '; i++){}
		if (line[i] == '#'){
			continue;
		}
		if (line[i] == '>'){
			i++;
			if (line[i] == '-'){
				current = new Block();
				leftMost = current;
				current->addToList(VisBlocks);
				colNum++;
			}else
			if (line[i] == '>'){
				tempNew = new Block();
				current->setRight(tempNew);
				tempNew->setLeft(current);
				if (current->getUp() && current->getUp()->getRight()){
					tempNew->setUp(current->getUp()->getRight());
					current->getUp()->getRight()->setDown(tempNew);
				}
				current = tempNew;
				current->addToList(VisBlocks);
				colNum++;
			}else
			if (line[i] == 'v'){
				tempNew = new Block();
				tempNew->setUp(leftMost);
				leftMost->setDown(tempNew);
				current = tempNew;
				leftMost = current;
				current->addToList(VisBlocks);
				if (allColNum == 0){
					allColNum = colNum;
				}
				else if (colNum != allColNum){
					//error case
					std::cerr << "ERROR: inconsistent column counts due to line " << lineNum << std::endl;
					return -1;
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
		if (objectType>0 && objectType<objectCount){
			current->addObject(objectIndex[objectType]->new_instance());
		}
		else{
			//error case
			std::cerr << "ERROR: no such object, line " << lineNum << std::endl;
			return -1;
		}


	}
	return 0;
}

int Map::getInt(char* text, int& start, int end){
	int result = 0;
	for (start = 0; text[start] == ' '; start++){}
	while (start < end && text[start] <= '9' && text[start] >= '0'){
		result = result * 10 + text[start] - '0';
	}
	return result;
}