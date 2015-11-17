#include "core.h"
#include "KriegMap.h"
#include <fstream>
//#include <vld.h>

bool running=true;

int main(int argc, char *argv[]){
	const Uint8 * m_keystate;
	int nkeys = 0;
	double topspeed = 10;
	double accel = 0.4;
	double speedx = 0, speedy = 0;
	double damp = 0.15;

	Sprite::createDefaultWindow("projKrieg", 30, 30, 640, 480, false);
	Sprite::setTargetFPS(60);
	KriegMap* map = new KriegMap(200, 200, 640, 480);
	map->loadMapFromFile("sampleMap.kmap");
	SDL_GetKeyboardState(&nkeys);
	m_keystate = SDL_GetKeyboardState(0);
	while (running){
		SDL_PumpEvents();
		//Sprite* sprite4 = Sprite::loadSprite("back.bmp");
		//Sprite::deleteSprite(sprite4);
		if (m_keystate[SDL_SCANCODE_ESCAPE] == 1){
			running = false;
		}
		
		
		Sprite::renderSprites();
		SDL_FlushEvents(SDL_QUIT, SDL_DROPFILE);
	}

	return 0;

}



int alt_main(int argc, char *argv[]){
	const Uint8 * m_keystate;
	int nkeys = 0;
	double topspeed = 10;
	double accel = 0.4;
	double speedx=0,speedy=0;
	double damp = 0.15;
	
	Sprite::createDefaultWindow("projKrieg",30,30,640,480,false);
	Sprite::setTargetFPS(60);
	Sprite* mysprite = Sprite::loadSprite("h1.bmp",10);
	mysprite->addImage("h2.bmp");
	mysprite->addImage("h3.bmp");
	mysprite->addImage("h4.bmp");
	mysprite->addImage("h5.bmp");
	mysprite->addImage("h6.bmp");
	mysprite->addImage("h7.bmp");
	mysprite->addImage("h8.bmp");
	mysprite->addImage("h9.bmp");
	mysprite->addImage("h10.bmp");
	mysprite->setImageColorKey(-1,true,0,0,0);
	Sprite* sprite2 = Sprite::loadSprite("back.bmp");
	Sprite* sprite3 = Sprite::loadSprite("humanity.bmp",1);
	sprite3->setImageColorKey(0,true,0,0,0);
	sprite3->setPriority(1);
	sprite3->sizeTo(200,300);
	sprite2->sizeTo(640,480);
	sprite2->setPriority(-1);
	SDL_GetKeyboardState(&nkeys);
	m_keystate = SDL_GetKeyboardState(0);
	mysprite->moveTo(400,300);
	sprite3->moveTo(200,200);
	sprite3->sizeTo(50,70);
	mysprite->sizeTo(100,200);
	mysprite->setAnimationFPF(6);
	mysprite->setAnimationFrames(0,9);
	mysprite->setAllAlpaMod(100);
	mysprite->loopAnim();
	sprite3->setRelative(mysprite,true);
	
	
	while(running){
		SDL_PumpEvents();
		//Sprite* sprite4 = Sprite::loadSprite("back.bmp");
		//Sprite::deleteSprite(sprite4);
		if(m_keystate[SDL_SCANCODE_ESCAPE]==1){
			running=false;
		}
		double realaccel = (accel*Sprite::getTargetFPS())/Sprite::getFPS();
		if(sqrt(speedx*speedx+speedy*speedy)<topspeed){
			if(m_keystate[SDL_SCANCODE_A]==1){
				speedx-=realaccel;
				if(abs(speedy)>abs(speedx)){
					if(m_keystate[SDL_SCANCODE_W]==1){
						speedy+=realaccel;
					}else if(m_keystate[SDL_SCANCODE_S]==1){
						speedy-=realaccel;
					}
				}
			}
			if(m_keystate[SDL_SCANCODE_W]==1){
				speedy-=realaccel;
				if(abs(speedx)>abs(speedy)){
					if(m_keystate[SDL_SCANCODE_A]==1){
						speedx+=realaccel;
					}else if(m_keystate[SDL_SCANCODE_D]==1){
						speedx-=realaccel;
					}
				}
			}
			if(m_keystate[SDL_SCANCODE_D]==1){
				speedx+=realaccel;
				if(abs(speedy)>abs(speedx)){
					if(m_keystate[SDL_SCANCODE_W]==1){
						speedy+=realaccel;
					}else if(m_keystate[SDL_SCANCODE_S]==1){
						speedy-=realaccel;
					}
				}
			}
			if(m_keystate[SDL_SCANCODE_S]==1){
				speedy+=realaccel;
				if(abs(speedx)>abs(speedy)){
					if(m_keystate[SDL_SCANCODE_A]==1){
						speedx+=realaccel;
					}else if(m_keystate[SDL_SCANCODE_D]==1){
						speedx-=realaccel;
					}
				}
			}
		}
		//std::cerr<<sqrt(speedx*speedx+speedy*speedy)<<std::endl;
		if(m_keystate[SDL_SCANCODE_Q]==1){
			mysprite->setAngle(mysprite->getAngle()-5,false);
		}
		if(m_keystate[SDL_SCANCODE_E]==1){
			mysprite->setAngle(mysprite->getAngle()+5,false);
		}
		
		double realdamp = (damp*Sprite::getTargetFPS())/Sprite::getFPS();
		if(speedx<0){
			speedx+=realdamp;
		}else if(speedx>0){
			speedx-=realdamp;
		}
		if(speedy<0){
			speedy+=realdamp;
		}else if(speedy>0){
			speedy-=realdamp;
		}
		if(abs(speedx)<realdamp){
			speedx=0;
		}
		if(abs(speedy)<realdamp){
			speedy=0;
		}
		mysprite->moveTo(mysprite->X()+speedx,mysprite->Y()+speedy,false);

		ColState state=mysprite->autoCol(sprite3);
		if(state == OBJ_LEFT || state == OBJ_RIGHT){
			speedx=0;
			speedy/=1.1;
		}
		if(state == OBJ_UP || state == OBJ_DOWN){
			speedy=0;
			speedx/=1.1;
		}

		Sprite::renderSprites();
		SDL_FlushEvents(SDL_QUIT,SDL_DROPFILE);
	}

	return 0;

}