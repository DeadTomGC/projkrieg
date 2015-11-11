#include "Factory.h"

int lastObject;

__declspec(dllexport) Object* __stdcall getObject(std::string name){
	//add object type creation here:






	
	return NULL;
	
}

__declspec(dllexport) Object* __stdcall getObjectByIndex(int index){
	//add object type creation here:







	return NULL;

}

__declspec(dllexport) Object* __stdcall getFirstObject(){
	//add object type creation here:
	lastObject = 0;
	return getObjectByIndex(lastObject);

}
__declspec(dllexport) Object* __stdcall getNextObject(){
	//add object type creation here:
	lastObject++;
	return getObjectByIndex(lastObject);
}

__declspec(dllexport) int __stdcall getTypeCount(){
	//add object type creation here:
	return 0;
}
