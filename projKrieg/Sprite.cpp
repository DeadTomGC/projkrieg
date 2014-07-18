#include "Sprite.h"
#include "SDL.h"
//#include <vld.h>

Sprite::PriList* Sprite::zero=NULL;
SDL_Renderer* Sprite::defaultRenderer=NULL;

Sprite::Sprite(){
	renderer=defaultRenderer;
	curImage=0;
	next=NULL;
	prev=NULL;
	priList=NULL;
	dstrect=NULL;
	srcrect=NULL;
	vis = true;
	angle = 0;
	center = new SDL_Point();
	flip = SDL_FLIP_NONE;
	x=y=0;
}

Sprite* Sprite::loadSprite(std::string bmp,int imageCount){
	if(defaultRenderer!=NULL && imageCount>0){
		Sprite* temp = new Sprite();
		temp->renderer=defaultRenderer;
		temp->imageCount=imageCount;
		temp->images=new Image*[imageCount];
		temp->images[0] = new Image();
		temp->images[0]->surface=SDL_LoadBMP(bmp.c_str());
		temp->images[0]->texture=SDL_CreateTextureFromSurface(defaultRenderer,temp->images[0]->surface);
		temp->images[0]->renderer = defaultRenderer;
		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=temp->images[0]->surface->w;
		temp->dstrect->h=temp->images[0]->surface->h;
		temp->center->x=temp->images[0]->surface->w/2;
		temp->center->y=temp->images[0]->surface->h/2;
		temp->dstrect->x=0;
		temp->dstrect->y=0;
		temp->nextImage=1;
		
		if(zero==NULL){
			zero = new PriList();
			zero->priority=0;
			zero->next=temp;
		}else{
			Sprite* temp2;
			temp2=zero->next;
			temp2->prev=temp;
			zero->next=temp;
			temp->next=temp2;
		}
		temp->priList=zero;

		return temp;
	}else{
		return NULL;
	}

}
Sprite* Sprite::loadSprite(std::string bmp,SDL_Renderer* renderer,int imageCount){
	if(imageCount>0){
		Sprite* temp = new Sprite();
		temp->renderer=renderer;
		temp->imageCount=imageCount;
		temp->images=new Image*[imageCount];
		temp->images[0] = new Image();
		temp->images[0]->surface=SDL_LoadBMP(bmp.c_str());
		temp->images[0]->texture=SDL_CreateTextureFromSurface(renderer,temp->images[0]->surface);
		temp->images[0]->renderer = renderer;
		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=temp->images[0]->surface->w;
		temp->dstrect->h=temp->images[0]->surface->h;
		temp->center->x=temp->images[0]->surface->w/2;
		temp->center->y=temp->images[0]->surface->h/2;
		temp->dstrect->x=0;
		temp->dstrect->y=0;
		temp->nextImage=1;
		
		if(zero==NULL){
			zero = new PriList();
			zero->priority=0;
			zero->next=temp;

		}else{
			Sprite* temp2;
			temp2=zero->next;
			zero->next=temp;
			temp->next=temp2;
		}
		temp->priList=zero;

		return temp;
	}else{
		return NULL;
	}

}

Sprite* Sprite::makeSprite(Image* img,int imageCount){
	if(defaultRenderer!=NULL && imageCount>0){
		Sprite* temp = new Sprite();
		temp->renderer=img->renderer;
		temp->imageCount=imageCount;
		temp->images=new Image*[imageCount];
		temp->images[0] = img;
		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=temp->images[0]->surface->w;
		temp->dstrect->h=temp->images[0]->surface->h;
		temp->center->x=temp->images[0]->surface->w/2;
		temp->center->y=temp->images[0]->surface->h/2;
		temp->dstrect->x=0;
		temp->dstrect->y=0;
		temp->nextImage=1;
		
		if(zero==NULL){
			zero = new PriList();
			zero->priority=0;
			zero->next=temp;
		}else{
			Sprite* temp2;
			temp2=zero->next;
			temp2->prev=temp;
			zero->next=temp;
			temp->next=temp2;
		}
		temp->priList=zero;

		return temp;
	}else{
		return NULL;
	}

}


void Sprite::setImageColorKey(int image,bool flag,Uint8 R,Uint8 G,Uint8 B,bool unshared){ //sets color key for image in sprite
	

		if(flag){
			SDL_SetColorKey(images[image]->surface,SDL_TRUE,SDL_MapRGB(images[image]->surface->format,R,G,B));
		}else{
			SDL_SetColorKey(images[image]->surface,SDL_FALSE,SDL_MapRGB(images[image]->surface->format,R,G,B));
		}
		
		//hmm should we delete the old texture?
		if(unshared){
			SDL_DestroyTexture(images[image]->texture);
		}
		images[image]->texture = SDL_CreateTextureFromSurface(renderer,images[image]->surface);
}

void Sprite::setPriority(int pri){
	PriList* current=zero;

	if(pri<current->priority){
		current=new PriList();
		current->priority=pri;
		current->nextHigher=zero;
		zero=current;

		clearFromList();

		current->next=this;
		prev=NULL;
		next=NULL;
		priList=current;

		return;
	}
	
	while(current->nextHigher!=NULL){
		if(current->nextHigher->priority<=pri){
			current = current->nextHigher;
		}else{
			break;
		}
	}
	if(current->priority==pri){
		clearFromList();
		next = current->next;
		next->prev=this;
		prev=NULL;
		priList=current;
		current->next=this;

	}else{

		current->nextHigher=new PriList();
		current = current->nextHigher;
		current->priority = pri;
		current->nextHigher = NULL;

		clearFromList();

		current->next=this;
		prev = NULL;
		next = NULL;
		priList = current;


	}

}


void Sprite::renderSprites(){
	PriList* currentL;
	Sprite* currentS;
	RenderLink* temp = NULL;
	currentL=zero;

	while(currentL!=NULL){
		currentS=currentL->next;
		while(currentS!=NULL){
			if(currentS->vis){
				SDL_RenderCopyEx(currentS->renderer, currentS->images[currentS->curImage]->texture, currentS->srcrect, currentS->dstrect,currentS->angle,currentS->center,currentS->flip); //add textures to the appropriate renderers.
				if(temp==NULL){
					temp = new RenderLink();
					temp->rend=currentS->renderer;
				}else{
					RenderLink* current = temp;
					bool notFound=true;
					while(current!=NULL){
						if(current->rend == currentS->renderer)
							notFound = false;
						current = current->next;
					}
					if(notFound){
						RenderLink* temp2 = temp;
						temp = new RenderLink();
						temp->rend=currentS->renderer;
						temp->next=temp2;
					}
				}
			}
			currentS=currentS->next;
		}
		currentL=currentL->nextHigher;
	}
	RenderLink* current = temp;
	RenderLink* del;
	while(current!=NULL){//render all frames
		SDL_RenderPresent(current->rend);
		del = current;
		current = current->next;
		delete del;
	}
}

void Sprite::addImage(std::string bmp){

	if(nextImage<imageCount){
		images[nextImage] = new Image();
		images[nextImage]->surface=SDL_LoadBMP(bmp.c_str());
		images[nextImage]->texture=SDL_CreateTextureFromSurface(renderer,images[nextImage]->surface);
		images[nextImage]->renderer = renderer;
		nextImage++;
	}

}

void Sprite::addImage(Image* img){

	if(nextImage<imageCount){
		if(img->renderer!=renderer){
			images[nextImage] = new Image();
			images[nextImage]->renderer = renderer;
			images[nextImage]->surface = img->surface;
			images[nextImage]->texture=SDL_CreateTextureFromSurface(renderer,images[nextImage]->surface);
		}else{
			images[nextImage] = img;
		}
		nextImage++;
	}

}

Sprite* Sprite::cloneSprite(Sprite* original){
	if(original!=NULL){
		Sprite* temp = new Sprite();
		temp->renderer=original->renderer;
		temp->imageCount=original->imageCount;
		temp->images=new Image*[original->imageCount];
		for(int i=0;i<original->imageCount;i++){
			temp->images[i]=original->images[i];
		}
		temp->nextImage=original->nextImage;

		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=original->dstrect->w;
		temp->dstrect->h=original->dstrect->h;
		temp->dstrect->x=original->dstrect->x;
		temp->dstrect->y=original->dstrect->y;
		
		if(original->srcrect!=NULL){
			temp->srcrect = new SDL_Rect();
			temp->srcrect->w=original->srcrect->w;
			temp->srcrect->h=original->srcrect->h;
			temp->srcrect->x=original->srcrect->x;
			temp->srcrect->y=original->srcrect->y;
		}
		
		Sprite* temp2;
		temp2=zero->next;
		zero->next=temp;
		temp->next=temp2;
		
		temp->priList=zero;

		temp->setPriority(original->priList->priority);
		return temp;
	}else{
		return NULL;
	}
}


Sprite* Sprite::cloneSprite(Sprite* original,SDL_Renderer* renderer){
	if(original!=NULL){
		Sprite* temp = new Sprite();
		temp->renderer=renderer;
		temp->imageCount=original->imageCount;
		temp->images=new Image*[original->imageCount];
		for(int i=0;i<original->imageCount;i++){
			temp->images[i]=new Image();
			temp->images[i]->renderer=renderer;
			temp->images[i]->surface=original->images[i]->surface;
			temp->images[i]->texture=SDL_CreateTextureFromSurface(renderer,temp->images[i]->surface);
		}
		temp->nextImage=original->nextImage;

		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=original->dstrect->w;
		temp->dstrect->h=original->dstrect->h;
		temp->dstrect->x=original->dstrect->x;
		temp->dstrect->y=original->dstrect->y;
		
		if(original->srcrect!=NULL){
			temp->srcrect = new SDL_Rect();
			temp->srcrect->w=original->srcrect->w;
			temp->srcrect->h=original->srcrect->h;
			temp->srcrect->x=original->srcrect->x;
			temp->srcrect->y=original->srcrect->y;
		}
		
		Sprite* temp2;
		temp2=zero->next;
		zero->next=temp;
		temp->next=temp2;
		
		temp->priList=zero;

		temp->setPriority(original->priList->priority);
		return temp;
	}else{
		return NULL;
	}
}


void Sprite::deleteSprite(Sprite* sprite,bool deleteResources){
	if(!deleteResources){
		sprite->clearFromList();
		delete sprite;
	}else{
		sprite->clearFromList();
		for(int i=0;i<sprite->nextImage;i++){//we don't delete renderers...
			SDL_FreeSurface(sprite->images[i]->surface);
			SDL_DestroyTexture(sprite->images[i]->texture);
			delete (sprite->images[i]);
		}
		delete sprite;
	}

}

Parr* Sprite::rectCol(Sprite* obj){//doesn't check verticies or for angled collisions
	Parr* inters=new Parr();       //IMPORTANT!!! DELETE THE Parr* AFTER USE!!!!
	Point* temp;
	if(temp=intersection(Point(dstrect->x,dstrect->y),Point(dstrect->x,dstrect->y+dstrect->h),Point(obj->dstrect->x,obj->dstrect->y),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y))){
		inters->add(temp);
	}
	if(temp=intersection(Point(dstrect->x+dstrect->w,dstrect->y),Point(dstrect->x+dstrect->w,dstrect->y+dstrect->h),Point(obj->dstrect->x,obj->dstrect->y),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y))){
		inters->add(temp);
	}
	if(temp=intersection(Point(dstrect->x,dstrect->y),Point(dstrect->x,dstrect->y+dstrect->h),Point(obj->dstrect->x,obj->dstrect->y+obj->dstrect->h),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y+obj->dstrect->h))){
		inters->add(temp);
	}
	if(temp=intersection(Point(dstrect->x+dstrect->w,dstrect->y),Point(dstrect->x+dstrect->w,dstrect->y+dstrect->h),Point(obj->dstrect->x,obj->dstrect->y+obj->dstrect->h),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y+obj->dstrect->h))){
		inters->add(temp);
		//
	}
	if(temp=intersection(Point(dstrect->x,dstrect->y),Point(dstrect->x+dstrect->w,dstrect->y),Point(obj->dstrect->x,obj->dstrect->y),Point(obj->dstrect->x,obj->dstrect->y+obj->dstrect->h))){
		inters->add(temp);
	}
	if(temp=intersection(Point(dstrect->x,dstrect->y+dstrect->h),Point(dstrect->x+dstrect->w,dstrect->y+dstrect->h),Point(obj->dstrect->x,obj->dstrect->y),Point(obj->dstrect->x,obj->dstrect->y+obj->dstrect->h))){
		inters->add(temp);
	}
	if(temp=intersection(Point(dstrect->x,dstrect->y),Point(dstrect->x+dstrect->w,dstrect->y),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y+obj->dstrect->h))){
		inters->add(temp);
	}
	if(temp=intersection(Point(dstrect->x,dstrect->y+dstrect->h),Point(dstrect->x+dstrect->w,dstrect->y+dstrect->h),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y),Point(obj->dstrect->x+obj->dstrect->w,obj->dstrect->y+obj->dstrect->h))){
		inters->add(temp);
	}
	if(inters->pointC==0){
		delete inters;
		return NULL;
	}else{
		return inters;
	}
}

ColState Sprite::autoCol(Sprite* obj){
	Parr* points;
	ColState state;
	points = rectCol(obj);
	if(points == NULL){
		return NONE;
	}else if(points->pointC>=2){
		Point center(obj->dstrect->x+(obj->dstrect->w)/2,obj->dstrect->y+(obj->dstrect->h)/2);

		if(points->arr[0]->x==points->arr[1]->x){
			if(points->arr[0]->x>center.x){
				moveTo(obj->dstrect->x+obj->dstrect->w+1,Y());
				state=OBJ_LEFT;
			}else{
				moveTo(obj->dstrect->x-dstrect->w-1,Y());
				state=OBJ_RIGHT;
			}
		}else if(points->arr[0]->y==points->arr[1]->y){
			if(points->arr[0]->y>center.y){
				moveTo(X(),obj->dstrect->y+obj->dstrect->h+1);
				state=OBJ_UP;
			}else{
				moveTo(X(),obj->dstrect->y-dstrect->h-1);
				state=OBJ_DOWN;
			}
		}else if(abs(points->arr[0]->x-points->arr[1]->x) >= abs(points->arr[0]->y - points->arr[1]->y)){
			if((points->arr[0]->y+points->arr[1]->y)/2>center.y){
				moveTo(X(),obj->dstrect->y+obj->dstrect->h+1);
				state=OBJ_UP;
			}else{
				moveTo(X(),obj->dstrect->y-dstrect->h-1);
				state=OBJ_DOWN;
			}
		}else{
			if((points->arr[0]->x+points->arr[1]->x)/2>center.x){
				moveTo(obj->dstrect->x+obj->dstrect->w+1,Y());
				state=OBJ_LEFT;
			}else{
				moveTo(obj->dstrect->x-dstrect->w-1,Y());
				state=OBJ_RIGHT;
			}
		}
		delete points;
		return state;
	}else{
		delete points;
		return NONE;
	}
}