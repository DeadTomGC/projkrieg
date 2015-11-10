#pragma once
#include <string>
#include "object.h" //add all custom object headers here


Object* __declspec(dllexport) __stdcall getObject(std::string name);
Object* __declspec(dllexport) __stdcall getObjectByIndex(int index);
Object* __declspec(dllexport) __stdcall getFirstObject();
Object* __declspec(dllexport) __stdcall getNextObject();
int __declspec(dllexport) __stdcall getTypeCount();