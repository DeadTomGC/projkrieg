#include "object.h"

void Object::addToList(Object* &firstInList){
	if (firstInList){
		this->next = firstInList;
		firstInList->prev = this;
		firstInList = this;
	}
	else{
		firstInList = this;
	}

}