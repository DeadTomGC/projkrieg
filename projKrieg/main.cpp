#include "Sprite.h"
#include "SDL.h"

//#include <vld.h>

bool running=true;
int main(int argc, char *argv[]){
	const Uint8 * m_keystate;
	int nkeys = 0;
	double topspeed = 5;
	double accel = 0.3;
	double speedx=0,speedy=0;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow( "projKrieg",100,100,640, 480, SDL_WINDOW_OPENGL );
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

	Sprite::setDefaultRenderer(renderer);
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
	mysprite->setImageColorKey(-1,true,0,0,0,1);
	Sprite* sprite2 = Sprite::loadSprite("back.bmp");
	Sprite* sprite3 = Sprite::loadSprite("humanity.bmp",1);
	sprite3->setImageColorKey(0,true,0,0,0,1);
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
	mysprite->loopAnim();
	sprite3->setRelative(mysprite,true);
	while(running){
		SDL_PumpEvents();
		if(m_keystate[SDL_SCANCODE_ESCAPE]==1){
			running=false;
		}
		if(sqrt(speedx*speedx+speedy*speedy)<topspeed){
			if(m_keystate[SDL_SCANCODE_A]==1){
				
				speedx-=accel;
				if(abs(speedy)>abs(speedx)){
					if(m_keystate[SDL_SCANCODE_W]==1){
						speedy+=accel;
					}else if(m_keystate[SDL_SCANCODE_S]==1){
						speedy-=accel;
					}
				}
			}
			if(m_keystate[SDL_SCANCODE_W]==1){
				speedy-=accel;
				if(abs(speedx)>abs(speedy)){
					if(m_keystate[SDL_SCANCODE_A]==1){
						speedx+=accel;
					}else if(m_keystate[SDL_SCANCODE_D]==1){
						speedx-=accel;
					}
				}
			}
			if(m_keystate[SDL_SCANCODE_D]==1){
				speedx+=accel;
				if(abs(speedy)>abs(speedx)){
					if(m_keystate[SDL_SCANCODE_W]==1){
						speedy+=accel;
					}else if(m_keystate[SDL_SCANCODE_S]==1){
						speedy-=accel;
					}
				}
			}
			if(m_keystate[SDL_SCANCODE_S]==1){
				speedy+=accel;
				if(abs(speedx)>abs(speedy)){
					if(m_keystate[SDL_SCANCODE_A]==1){
						speedx+=accel;
					}else if(m_keystate[SDL_SCANCODE_D]==1){
						speedx-=accel;
					}
				}
			}
		}
		//std::cerr<<sqrt(speedx*speedx+speedy*speedy)<<std::endl;
		if(m_keystate[SDL_SCANCODE_Q]==1){
			mysprite->setAngle(mysprite->getAngle()-5);
		}
		if(m_keystate[SDL_SCANCODE_E]==1){
			mysprite->setAngle(mysprite->getAngle()+5);
		}
		

		if(speedx<0){
			speedx+=0.15;
		}else if(speedx>0){
			speedx-=0.15;
		}
		if(speedy<0){
			speedy+=0.15;
		}else if(speedy>0){
			speedy-=0.15;
		}
		if(abs(speedx)<0.15){
			speedx=0;
		}
		if(abs(speedy)<0.15){
			speedy=0;
		}
		mysprite->moveTo(mysprite->X()+speedx,mysprite->Y()+speedy);

		ColState state=mysprite->autoCol(sprite3);
		if(state == OBJ_LEFT || state == OBJ_RIGHT){
			speedx=0;
			speedy/=1.1;
		}
		if(state == OBJ_UP || state == OBJ_DOWN){
			speedy=0;
			speedx/=1.1;
		}

		/*Parr* temp;
		if(temp=mysprite->rectCol(sprite3)){
			sprite2->setVisible(false);
		}else{
			sprite2->setVisible(true);
		}*/
		Sprite::renderSprites();
	}

	return 0;

}