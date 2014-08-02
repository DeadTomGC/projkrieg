#pragma once
#include <string>
#include "SDL.h"
#include "utils.h"
#include <time.h>
//#include <vld.h>

class Surface{ //a container that allows references to be counted s is the actual surface
public:
	Surface(SDL_Surface* surface){s=surface;count=1;user=false;}
	SDL_Surface* s;
	int count;
	bool user;
	~Surface(){SDL_FreeSurface(s);}
};
class Texture{ //a container that allows references to be counted t is the actual texture
public:
	Texture(SDL_Texture* texture){t=texture;count=1;user=false;}
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



class Sprite{
public:
	static void setDefaultRenderer(SDL_Renderer* renderer){defaultRenderer = renderer;}
	static void renderSprites();
	static Image* loadImage(std::string bmp,SDL_Renderer* renderer=defaultRenderer);
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
	
	void setImageColorKey(int sprite,bool flag,Uint8 R,Uint8 G,Uint8 B);//a negitive sprite index will set all the color keys
	void setPriority(int pri);
	Parr* rectCol(Sprite* obj);//IMPORTANT!!! DELETE THE Parr* AFTER USE!!!!
	ColState autoCol(Sprite* obj);
	bool setAllAlpaMod(Uint8 alpha);
	
	void setRelative(Sprite* host,bool sameRotCenter=false);
	void disableRelative();

	void setAnimationFrames(int start,int end){startF=start;endF=end;}
	
	void playAnim(){animate = true;loop = false;frameCounter=0;curImage=startF;}
	void loopAnim(){animate = true;loop = true;frameCounter=0;curImage=startF;}
	void pauseAnim(){animate = false;}
	void stopAnim(){animate = false;curImage=startF;}
	void contAnim(){animate = true;}

	void setAnimationFPF(int fpf){this->fpf=fpf;}
	void setRotCenter(int x,int y){center->x=x,center->y=y;}
	int rotCentX(){return center->x;}
	int rotCentY(){return center->y;}
	double getAngle(){return angle;}
	void setAngle(double angle,bool abs = true);
	double X(void){return x;}
	double Y(void){return y;}
	void moveTo(double x,double y,bool abs = true);
	void sizeTo(int w,int h){dstrect->w=w;dstrect->h=h;center->x=w/2;center->y=h/2;}
	void setVisible(bool vis){this->vis=vis;}
	bool isVisible(){return vis;}
protected:
	//classes:
	struct ColorKey{
		Uint32 colorKey;
		int flag;
	};
	class SpriteCont{//used to keep track of relative sprites
	public:
		SpriteCont(){next=NULL;sprite=NULL;}
		SpriteCont* next;
		Sprite* sprite;
	};
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
	
	void animUD();//updates animations
	//static vars:
	static int framesToAverage;
	static double fps,targetfps;
	static PriList* zero;//the lowest priority that starts at 0 but may not remain there
	static SDL_Renderer* defaultRenderer;//the default renderer
	//non-static vars:
	ColorKey* keys;
	SDL_Rect *dstrect,*srcrect;//destination rectangle and source rectanlge
	Uint8 alpha;
	double x,y;
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
	Sprite *next,*prev,*host;//the next and previous sprite in the PriList
	PriList* priList;//priList that the sprite is linked to
	SpriteCont* relFirst; //the first in a list of sprites that are to be positioned relative to this one.
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
	void decTexture(Texture* texture){
		texture->count-=1;
		if(texture->count==0 && texture->user==false){
			delete texture;
		}
	}
	void decSurface(Surface* surface){
		surface->count-=1;
		if(surface->count==0 && surface->user==false){
			delete surface;
		}
	}
	Sprite();
	Sprite(Sprite &s);
	~Sprite(){}

};

