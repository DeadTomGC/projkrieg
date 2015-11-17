#pragma once
#include <string>
#include "SDL.h"
#include "utils.h"
#include "core.h"
#include <time.h>
//#include <vld.h>

class Surface{ //a container that allows references to be counted s is the actual surface
public:
	Surface(SDL_Surface* surface){this->s=surface;count=1;user=false;}
	SDL_Surface* s;
	int count;
	bool user;
	~Surface(){SDL_FreeSurface(s);}
};
class Texture{ //a container that allows references to be counted t is the actual texture
public:
	Texture(SDL_Texture* texture){this->t=texture;count=1;user=false;}
	SDL_Texture* t;
	int count;
	bool user;
	~Texture(){SDL_DestroyTexture(t);}
};


struct Image{
	Surface* surface;
	Texture* texture;
	SDL_Renderer* renderer;
};


enum ColState{
	NONE,
	OBJ_LEFT,
	OBJ_RIGHT,
	OBJ_UP,
	OBJ_DOWN
};

struct ColorKey{
	Uint32 colorKey;
	int flag;
};
class SpriteCont{//used to keep track of relative sprites
public:
	SpriteCont(){ next = NULL; sprite = NULL; }
	SpriteCont* next;
	Sprite* sprite;
};
class PriList{//used as a single priority (keeps all sprites at this level)
public:
	PriList(){
		priority = -5000;
		nextHigher = NULL;
		next = NULL;
	}
	int priority;
	PriList* nextHigher;
	Sprite* next;
};
class RenderLink{//used to keep track of all the renderers used by tracked sprites
public:
	RenderLink(){
		next = NULL;
		rend = NULL;
	}
	RenderLink* next;
	SDL_Renderer* rend;
};

class Sprite{
public:
	static void createDefaultWindow(std::string windowName,int x,int y,int sizeX,int sizeY,bool vsync);
	static SDL_Window* getDefaultWindow(){ if (ssd) return ssd->defaultWindow; return NULL; }
	static SDL_Renderer* getDefaultRenderer(){ if (ssd) return ssd->defaultRenderer; return NULL; }
	static void setDefaultRenderer(SDL_Renderer* renderer){ if (ssd) ssd->defaultRenderer = renderer; }
	static void setDefaultWindow(SDL_Window* window){ if (ssd) ssd->defaultWindow = window; }
	static void renderSprites();
	static double getFPS(){ if (ssd) return ssd->fps;  return NULL; }
	static void setTargetFPS(double targetfps){ if (ssd) ssd->targetfps = targetfps; }
	static double getTargetFPS(){ if (ssd) return ssd->targetfps;  return NULL; }
	static Image* loadImage(std::string bmp,SDL_Renderer* renderer=NULL); 
	static Sprite* loadSprite(std::string bmp,int imageCount=1);
	static Sprite* loadSprite(std::string bmp,SDL_Renderer* renderer,int imageCount=1);
	static Sprite* makeSprite(Image* img,int imageCount=1);
	static Sprite* cloneSprite(Sprite* original);
	static Sprite* cloneSprite(Sprite* original,SDL_Renderer* renderer);
	static void deleteSprite(Sprite* sprite);
	static void setSSD(SharedSpriteData* ssd){Sprite::ssd = ssd;}
	static SharedSpriteData* getSSD(){ return ssd; }
	//non-static functions:
	void setImage(int i){curImage = i;}
	void addImage(std::string bmp);
	void addImage(Image* img);
	
	void setImageColorKey(int image,bool flag,Uint8 R,Uint8 G,Uint8 B);//a negitive sprite index will set all the color keys
	void setPriority(int pri);
	Parr* rectCol(Sprite* obj);//IMPORTANT!!! DELETE THE Parr* AFTER USE!!!!
	ColState autoCol(Sprite* obj);
	bool setAllAlpaMod(Uint8 alpha);
	
	void setRelative(Sprite* host,bool sameRotCenter=false);
	void disableRelative();

	void setAnimationFrames(int start,int end){startF=start;endF=end;}

	void setFrame(int frame){if(frame>0 && frame<this->nextImage)curImage=frame;} //bad
	void playAnim(){animate = true;loop = false;frameCounter=0;curImage=startF;}
	void loopAnim(){animate = true;loop = true;frameCounter=0;curImage=startF;}
	void pauseAnim(){animate = false;}
	void stopAnim(){animate = false;curImage=startF;}
	void contAnim(){animate = true;}

	void setFlip(SDL_RendererFlip mode){flip = mode;}
	int getImageColorKey(int i,Uint32& colorKey){colorKey=this->keys[i].colorKey;return this->keys[i].flag;}
	void setAnimationFPF(int fpf){this->fpf=fpf;} //set animations frames perframe of animation
	void setRotCenter(int x,int y){center->x=x,center->y=y;}
	int rotCentX(){return center->x;}
	int rotCentY(){return center->y;}
	double getAngle(){return angle;}
	void setAngle(double angle,bool abs = true); //accounts for fps if you have abs be false
	double X(void){return x;}
	double Y(void){return y;}
	void moveTo(double x,double y,bool abs = true);//accounts for fps if you have abs be false
	void sizeTo(int w,int h){dstrect->w=w;dstrect->h=h;center->x=w/2;center->y=h/2;}
	void setDrawRegion(int x,int y,int w,int h);
	int getDRX();
	int getDRY();
	int getDRW();
	int getDRH();
	void setVisible(bool vis){this->vis=vis;}
	bool isVisible(){return vis;}

	//utility
	void addToList(Sprite* &firstInList); //add to a user's linked list
	//for maniplulating the linked list created by the user
	Sprite* getNext(); 
	void setNext(Sprite* next);
	Sprite* getPrev();
	void setPrev(Sprite* prev);

protected:
	void animUD();//updates animations
	//static vars:
	static SharedSpriteData* ssd;//shared sprite data
	//non-static vars:
	ColorKey* keys;// array of color keys for all images
	SDL_Rect *dstrect,*srcrect;//destination rectangle and source rectanlge
	Uint8 alpha;//alpha value for whole sprite
	double x,y; //location
	bool animate,loop; //animate?
	int startF,endF; //set the image number to start on and the image number to end on
	double frameCounter; //used to keep track of passed frames
	double fpf; // the number of frames per frame
	int imageCount;//max images
	int nextImage;//where to place next image in array
	int curImage;//which image will be rendered
	double angle;//angle to render at
	SDL_Point* center;//center from where to rotate
	SDL_RendererFlip flip;//what flip mode
	SDL_Renderer* renderer;//which renderer to render with
	Image** images;//array of image pointers
	Sprite *next,*prev,*host,*userNext,*userPrev;//the next and previous sprite in the PriList, host is the parent sprite when relative is enabled
	PriList* priList;//priList that the sprite is linked to
	SpriteCont* relFirst; //the first in a list of sprites that are to be positioned relative to this one.
	bool vis;//should the sprite be rendered?
private:
	//helper that clears the current sprite from the render list
	void clearFromList(){
		if(prev==NULL){
			priList->next=next;	
		}else{
			prev->next=next;
		}
		if(next!=NULL)
				next->prev=prev;
	}
protected:
	//helpers for clearing up shared textures and surfaces
	static void decTexture(Texture* texture){
		texture->count-=1;
		if(texture->count==0 && texture->user==false){
			delete texture;
		}
	}
	static void decSurface(Surface* surface){
		surface->count-=1;
		if(surface->count==0 && surface->user==false){
			delete surface;
		}
	}
private:
	Sprite();
	Sprite(Sprite &s);
	~Sprite(){}

};

