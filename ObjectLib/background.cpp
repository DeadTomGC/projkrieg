#include "background.h"

std::string Background::typeName = "Background";

Background::Background(Block* parent) : Object(parent){
	if (parent){
		primary = Sprite::loadSprite("h1.bmp", 10);

		primary->addImage("h2.bmp");
		primary->addImage("h3.bmp");
		primary->addImage("h4.bmp");
		primary->addImage("h5.bmp");
		primary->addImage("h6.bmp");
		primary->addImage("h7.bmp");
		primary->addImage("h8.bmp");
		primary->addImage("h9.bmp");
		primary->addImage("h10.bmp");
		primary->moveTo(0, 0);
		primary->sizeTo(parent->getSizeX(), parent->getSizeY());
		primary->setAnimationFPF(10);
		primary->setAnimationFrames(0, 9);
		primary->loopAnim();
		primary->addToList(first);
	}
}

void Background::update(void){
	
	if (parent){
		
		if (parent->getLeft()){
			Object* temp = parent->getLeft()->getFirstObject();
			while (temp){
				if (!temp->getTypeName()->compare(Background::typeName)){
					((Background*)temp)->primary->stopAnim();
				}
				temp = temp->getNext();
			}
		}
	}
}

