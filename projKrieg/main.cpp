#include "Sprite.h"
#include "SDL.h"
//#include <vld.h>

bool running=true;
int main(int argc, char *argv[]){
	const Uint8 * m_keystate;
	int nkeys = 0;

	double speedx,speedy;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow( "projKrieg",100,100,640, 480, SDL_WINDOW_OPENGL );
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

	Sprite::setDefaultRenderer(renderer);
	Sprite* mysprite = Sprite::loadSprite("humanity.bmp",2);
	mysprite->addImage("humanity2.bmp");
	mysprite->setImageColorKey(0,true,0,0,0,1);
	mysprite->setImageColorKey(1,true,0,0,0,1);
	Sprite* sprite2 = Sprite::loadSprite("back.bmp");
	Sprite* sprite3 = Sprite::cloneSprite(mysprite);
	sprite3->setPriority(1);
	sprite3->sizeTo(200,300);
	sprite2->sizeTo(640,480);
	sprite2->setPriority(-1);
	SDL_GetKeyboardState(&nkeys);
	m_keystate = SDL_GetKeyboardState(0);
	mysprite->moveTo(400,300);
	sprite3->moveTo(100,100);
	sprite3->sizeTo(50,70);
	mysprite->sizeTo(50,70);
	while(running){
		SDL_PumpEvents();
		if(m_keystate[SDL_SCANCODE_ESCAPE]==1){
			running=false;
		}
		if(m_keystate[SDL_SCANCODE_A]==1){
			speedx-=0.07;
		}
		if(m_keystate[SDL_SCANCODE_W]==1){
			speedy-=0.07;
		}
		if(m_keystate[SDL_SCANCODE_D]==1){
			speedx+=0.07;
		}
		if(m_keystate[SDL_SCANCODE_S]==1){
			speedy+=0.07;
		}
		if(m_keystate[SDL_SCANCODE_Q]==1){
			mysprite->setAngle(mysprite->getAngle()-5);
		}
		if(m_keystate[SDL_SCANCODE_E]==1){
			mysprite->setAngle(mysprite->getAngle()+5);
		}
		if(m_keystate[SDL_SCANCODE_SPACE]==1){
			mysprite->setImage(1);
		}else{
			mysprite->setImage(0);
		}

		speedx = speedx - speedx/100;
		speedy = speedy - speedy/100;
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