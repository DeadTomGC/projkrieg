#pragma once
#include <string>
#include "objectTypes.h" //add all custom object headers here

extern "C"{
	__declspec(dllexport) void setSSD(SharedSpriteData* ssd);
	__declspec(dllexport) Object* getObject(const std::string &name);
	__declspec(dllexport) Object* getObjectByIndex(int index);
	__declspec(dllexport) Object* getFirstObject();
	__declspec(dllexport) Object* getNextObject();
	__declspec(dllexport) int getTypeCount();
}