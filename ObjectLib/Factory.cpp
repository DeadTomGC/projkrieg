#include "Factory.h"

int lastObject;

extern "C"{
	__declspec(dllexport) void setSSD(SharedSpriteData* ssd){
		Sprite::setSSD(ssd);
	}
	__declspec(dllexport) Object* getObject(const std::string &name){
		//add object type creation here:
		if (!Background::typeName.compare(name)){
			return new Background(NULL);
		}

		return NULL;

	}

	__declspec(dllexport) Object* getObjectByIndex(int index){
		//add object type creation here:
		switch (index){
		case 0:
			return new Background(NULL);
			break;


		default:
			return NULL;
			break;
		}



	}

	__declspec(dllexport) Object* getFirstObject(){
		//add object type creation here:
		lastObject = 0;
		return getObjectByIndex(lastObject);

	}
	__declspec(dllexport) Object* getNextObject(){
		//add object type creation here:
		lastObject++;
		return getObjectByIndex(lastObject);
	}

	__declspec(dllexport) int getTypeCount(){
		//add object type creation here:
		return OBJECT_COUNT;
	}
	
}
