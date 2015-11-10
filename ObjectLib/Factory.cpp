#include "Factory.h"

int lastObject;

Object* __declspec(dllexport) __stdcall getObject(std::string name){
	//add object type creation here:






	
	return NULL;
	
}

Object* __declspec(dllexport) __stdcall getObjectByIndex(int index){
	//add object type creation here:







	return NULL;

}

Object* __declspec(dllexport) __stdcall getFirstObject(){
	//add object type creation here:
	lastObject = 0;
	return getObjectByIndex(lastObject);

}
Object* __declspec(dllexport) __stdcall getNextObject(){
	//add object type creation here:
	lastObject++;
	return getObjectByIndex(lastObject);
}

int __declspec(dllexport) __stdcall getTypeCount(){
	//add object type creation here:
	return 0;
}
