#include "Sprite.h"
#include "SDL.h"

bool running=true;
int main(int argc, char *argv[]){
	const Uint8 * m_keystate;
	int nkeys = 0;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow( "projKrieg",100,100,640, 480, SDL_WINDOW_OPENGL );
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

	Sprite::setDefaultRenderer(renderer);
	Sprite* mysprite = Sprite::loadSprite("humanity.bmp",2);
	mysprite->addImage("humanity2.bmp");
	mysprite->setImageColorKey(0,true,0,0,0,1);
	mysprite->setImageColorKey(1,true,0,0,0,1);
	Sprite* sprite2 = Sprite::loadSprite("back.bmp");
	Sprite* sprite3 = Sprite::makeSprite(mysprite->getImage(0));
	sprite3->setPriority(1);
	sprite3->sizeTo(200,300);
	sprite2->sizeTo(640,480);
	sprite2->setPriority(-1);
	SDL_GetKeyboardState(&nkeys);
	m_keystate = SDL_GetKeyboardState(0);
	while(running){
		SDL_PumpEvents();
		if(m_keystate[SDL_SCANCODE_ESCAPE]==1){
			running=false;
		}
		if(m_keystate[SDL_SCANCODE_A]==1){
			mysprite->moveTo(mysprite->X()-2,mysprite->Y());
		}
		if(m_keystate[SDL_SCANCODE_W]==1){
			mysprite->moveTo(mysprite->X(),mysprite->Y()-2);
		}
		if(m_keystate[SDL_SCANCODE_D]==1){
			mysprite->moveTo(mysprite->X()+2,mysprite->Y());
		}
		if(m_keystate[SDL_SCANCODE_S]==1){
			mysprite->moveTo(mysprite->X(),mysprite->Y()+2);
		}
		if(m_keystate[SDL_SCANCODE_F]==1){
			mysprite->setImage(1);
		}else{
			mysprite->setImage(0);
		}
		Sprite::renderSprites();
	}

	return 0;

}