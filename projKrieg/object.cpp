#include "object.h"

//Only contains functionality that is not likely to change

std::string Object::typeName = "Object";

Object::Object(Block* parent){
	next = prev = NULL;
	first = NULL;
	this->parent = parent;
	if (parent){
		this->map = parent->getMap();
	}
	else{
		this->map = NULL;
	}
}

void Object::hide(){
	Sprite* temp = first;
	while (temp){
		temp->setVisible(false);
		temp = temp->getNext();
	}

}

void Object::show(){
	Sprite* temp = first;
	while (temp){
		temp->setVisible(true);
		temp = temp->getNext();
	}
}

void Object::relocateObject(double changeX, double changeY){

	Sprite* temp = first;
	while (temp){
		if (map && parent)
		{
			temp->moveTo(changeX + temp->X(), changeY + temp->Y());
		}
		temp = temp->getNext();
	}


}