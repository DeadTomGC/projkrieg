#include "KriegBlock.h"

void KriegBlock::update(){
	Object *temp = first;
	while (temp != NULL){
		temp->update();
		temp = temp->getNext();
	}
}
KriegBlock::KriegBlock(){
	right = 0;
	left = 0;
	up = 0;
	down = 0;
	next = 0;
	prev = 0;
	first = 0;
	map = 0;
	upToDate = false;
}

void KriegBlock::addObject(Object* obj){
	obj->addToList(first);
}

void KriegBlock::addToList(Block* &firstInList){
	if (firstInList){
		this->next = firstInList;
		firstInList->setPrev(this);
		firstInList = this;
	}
	else{
		firstInList = this;
	}

}

void KriegBlock::checkView(){};
void KriegBlock::seekView(){};