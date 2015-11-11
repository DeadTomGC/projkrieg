#pragma once
#include <string>
#include "object.h" //add all custom object headers here


__declspec(dllexport) Object* __stdcall getObject(std::string name);
__declspec(dllexport) Object* __stdcall getObjectByIndex(int index);
__declspec(dllexport) Object* __stdcall getFirstObject();
__declspec(dllexport) Object* __stdcall getNextObject();
__declspec(dllexport) int __stdcall getTypeCount();