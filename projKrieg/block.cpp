#include "block.h"

void Block::update(){
	Object *temp = first;
	while (temp != NULL){
		temp->update();
		temp = temp->getNext();
	}
}
Block::Block(){
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

void Block::addObject(Object* obj){
	obj->addToList(first);
}

void Block::addToList(Block* &firstInList){
	if (firstInList){
		this->next = firstInList;
		firstInList->prev = this;
		firstInList = this;
	}
	else{
		firstInList = this;
	}

}