#pragma once
#include <string>
#include "SDL.h"
#include "utils.h"
//#include <vld.h>

struct Image{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
};




class Sprite{
public:
	static void setDefaultRenderer(SDL_Renderer* renderer){defaultRenderer = renderer;}
	static void renderSprites();
	static Sprite* loadSprite(std::string bmp,int imageCount=1);
	static Sprite* loadSprite(std::string bmp,SDL_Renderer* renderer,int imageCount=1);
	static Sprite* makeSprite(Image* img,int imageCount=1);
	static Sprite* cloneSprite(Sprite* original);
	static Sprite* cloneSprite(Sprite* original,SDL_Renderer* renderer);
	static void deleteSprite(Sprite* sprite,bool deleteResources=false);
	//non-static functions:
	void setImage(int i){curImage = i;}
	void addImage(std::string bmp);
	void addImage(Image* img);
	Image* getImage(int i){return images[i];}
	void setImageColorKey(int sprite,bool flag,Uint8 R,Uint8 G,Uint8 B,bool unshared=false);
	void setPriority(int pri);
	Parr* rectCol(Sprite* obj);//IMPORTANT!!! DELETE THE Parr* AFTER USE!!!!
	bool autoCol(Sprite* obj);

	double getAngle(){return angle;}
	void setAngle(double angle){this->angle=angle;}
	int X(void){return dstrect->x;}
	int Y(void){return dstrect->y;}
	void moveTo(int x,int y){dstrect->x=x;dstrect->y=y;}
	void sizeTo(int w,int h){dstrect->w=w;dstrect->h=h;center->x=w/2;center->y=h/2;}
	void setVisible(bool vis){this->vis=vis;}
protected:
	//classes:
	class PriList{//used as a single priority (keeps all sprites at this level)
	public:
		PriList(){
			priority=-5000;
			nextHigher=NULL;
			next=NULL;
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
	//static vars:
	static PriList* zero;//the lowest priority that starts at 0 but may not remain there
	static SDL_Renderer* defaultRenderer;//the default renderer
	//non-static vars:
	SDL_Rect *dstrect,*srcrect;//destination rectangle and source rectanlge
	int imageCount;//max images
	int nextImage;//where to place next image in array
	int curImage;//which image will be rendered
	double angle;//angle to render at
	SDL_Point* center;//center from where to rotate
	SDL_RendererFlip flip;//what flip mode
	SDL_Renderer* renderer;//which renderer to render with
	Image** images;//array of image pointers
	Sprite *next,*prev;//the next and previous sprite in the PriList
	PriList* priList;//priList that the sprite is linked to
	bool vis;
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
	Sprite();
	Sprite(Sprite &s);
	~Sprite(){}

};

