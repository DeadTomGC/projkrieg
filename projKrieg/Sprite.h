#include <string>
#include "SDL.h"
#include "utils.h"


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
	static void deleteSprite(Sprite* sprite,bool deleteResources=false);//TODO: handle delete true
	//non-static functions:
	void setImage(int i){curImage = i;}
	void addImage(std::string bmp);
	void addImage(Image* img);
	Image* getImage(int i){return images[i];}
	void setImageColorKey(int sprite,bool flag,Uint8 R,Uint8 G,Uint8 B,bool unshared=false);
	void setPriority(int pri);
	bool rectCol(Sprite* obj);//fix this using intersection
	
	int X(void){return dstrect->x;}
	int Y(void){return dstrect->y;}
	void moveTo(int x,int y){dstrect->x=x;dstrect->y=y;}
	void sizeTo(int w,int h){dstrect->w=w;dstrect->h=h;}
	void setVisible(bool vis){this->vis=vis;}
protected:
	//classes:
	class PriList{
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
	class RenderLink{
	public:
		RenderLink(){
			next = NULL;
			rend = NULL;
		}
		RenderLink* next;
		SDL_Renderer* rend;
	};
	//static vars:
	static PriList* zero;
	static SDL_Renderer* defaultRenderer;
	//non-static vars:
	SDL_Rect *dstrect,*srcrect;
	int imageCount,nextImage,curImage;
	SDL_Renderer* renderer;
	Image** images;
	Sprite *next,*prev;
	PriList* priList;
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

