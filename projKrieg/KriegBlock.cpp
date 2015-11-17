#include "KriegBlock.h"

void KriegBlock::update(){
	checkView();
	if (active){
		Object *temp = first;
		while (temp != NULL){
			temp->update();
			temp = temp->getNext();
		}
	}
}
KriegBlock::KriegBlock(Map* map) : Block(map){
	right = 0;
	left = 0;
	up = 0;
	down = 0;
	next = 0;
	prev = 0;
	first = 0;
	map = 0;
	active = false;
	upToDate = false;
}

void KriegBlock::addObject(Object* obj){
	obj->addToList(first);
}

void KriegBlock::deActivateAndHide(){
	if (map){
		if (active){
			if (prev){
				prev->setNext(next);
				if (next){
					next->setPrev(prev);
				}
			}
			else{
				if (next){
					next->setPrev(NULL);
				}
				map->setVisBlocks(next);
			}
			next = prev = NULL;

			Object* temp = first;
			while (temp){
				temp->hide();
				temp = temp->getNext();
			}

			active = false;
		}
	}

}

void KriegBlock::activateAndShow(){
	if (map){
		if (!active){
			next = map->getVisBlocks();

			if (next){
				next->setPrev(this);
			}

			prev = NULL;
			map->setVisBlocks(this);

			Object* temp = first;
			while (temp){
				temp->show();
				temp = temp->getNext();
			}

			active = true;
		}
	}

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

void KriegBlock::checkView(){
	if (map){
		if (x < map->getScreenOffsetX() || x > map->getScreenOffsetX() + map->getScreenW() || y < map->getScreenOffsetY() || y > map->getScreenOffsetY() + map->getScreenH()){
			//block is out of view
			this->deActivateAndHide();
		}
		else{
			this->activateAndShow();
		}

	}
};

void KriegBlock::seekView(){};