#include "Sprite.h"
#include "SDL.h"
//#include <vld.h>

Sprite::PriList* Sprite::zero=NULL;
SDL_Renderer* Sprite::defaultRenderer=NULL;

Sprite::Sprite(){
	renderer=defaultRenderer;
	host = NULL;
	curImage=0;
	fpf=1;
	relFirst = NULL;
	frameCounter = 0;
	animate = false;
	loop = false;
	startF=0;
	endF=0;
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

Sprite* Sprite::loadSprite(std::string bmp,int imageCount){//good
	if(defaultRenderer!=NULL && imageCount>0){
		Sprite* temp = new Sprite();
		temp->renderer=defaultRenderer;
		temp->imageCount=imageCount;
		temp->images=new Image*[imageCount];
		temp->images[0] = new Image();
		temp->images[0]->surface=new Surface(SDL_LoadBMP(bmp.c_str()));
		temp->images[0]->texture=new Texture(SDL_CreateTextureFromSurface(defaultRenderer,temp->images[0]->surface->s));
		temp->images[0]->renderer = defaultRenderer;
		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=temp->images[0]->surface->s->w;
		temp->dstrect->h=temp->images[0]->surface->s->h;
		temp->center->x=temp->images[0]->surface->s->w/2;
		temp->center->y=temp->images[0]->surface->s->h/2;
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
Sprite* Sprite::loadSprite(std::string bmp,SDL_Renderer* renderer,int imageCount){//good
	if(imageCount>0){
		Sprite* temp = new Sprite();
		temp->renderer=renderer;
		temp->imageCount=imageCount;
		temp->images=new Image*[imageCount];
		temp->images[0] = new Image();
		temp->images[0]->surface=new Surface(SDL_LoadBMP(bmp.c_str()));
		temp->images[0]->texture=new Texture(SDL_CreateTextureFromSurface(renderer,temp->images[0]->surface->s));
		temp->images[0]->renderer = renderer;
		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=temp->images[0]->surface->s->w;
		temp->dstrect->h=temp->images[0]->surface->s->h;
		temp->center->x=temp->images[0]->surface->s->w/2;
		temp->center->y=temp->images[0]->surface->s->h/2;
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

Sprite* Sprite::makeSprite(Image* img,int imageCount){//good
	if(img!=NULL && imageCount>0){
		Sprite* temp = new Sprite();
		temp->renderer=img->renderer;
		temp->imageCount=imageCount;
		temp->images=new Image*[imageCount];
		temp->images[0] = new Image();
		temp->images[0]->renderer = img->renderer;
		temp->images[0]->surface = img->surface;
		temp->images[0]->texture = img->texture;
		img->surface->count+=1;
		img->texture->count+=1;
		temp->dstrect = new SDL_Rect();
		temp->dstrect->w=temp->images[0]->surface->s->w;
		temp->dstrect->h=temp->images[0]->surface->s->h;
		temp->center->x=temp->images[0]->surface->s->w/2;
		temp->center->y=temp->images[0]->surface->s->h/2;
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


void Sprite::setImageColorKey(int image,bool flag,Uint8 R,Uint8 G,Uint8 B){ //sets color key for image in sprite //all good assuming that images are never shared
	Image* temp;
	Uint32 colorKey;
	int oldFlag;
	if(image<0){
		for(image=0;image<nextImage;image++){
			temp = new Image();
			temp->renderer=images[image]->renderer;
			temp->surface=images[image]->surface;
			temp->surface->count+=1;
			oldFlag = SDL_GetColorKey(images[image]->surface->s,&colorKey);
			if(flag){
				SDL_SetColorKey(images[image]->surface->s,SDL_TRUE,SDL_MapRGB(images[image]->surface->s->format,R,G,B));
			}else{
				SDL_SetColorKey(images[image]->surface->s,SDL_FALSE,SDL_MapRGB(images[image]->surface->s->format,R,G,B));
			}
			temp->texture=new Texture(SDL_CreateTextureFromSurface(renderer,images[image]->surface->s));
			if(oldFlag==0){
				SDL_SetColorKey(images[image]->surface->s,SDL_TRUE,colorKey);
			}else{
				SDL_SetColorKey(images[image]->surface->s,SDL_FALSE,colorKey);
			}
			//destroy old Image
			decSurface(images[image]->surface);
			decTexture(images[image]->texture);
			delete images[image];
			//set new image as the one to be used
			images[image] = temp;
		}
	}else{
		temp = new Image();
		temp->renderer=images[image]->renderer;
		temp->surface=images[image]->surface;
		temp->surface->count+=1;
		oldFlag = SDL_GetColorKey(images[image]->surface->s,&colorKey);
		if(flag){
			SDL_SetColorKey(images[image]->surface->s,SDL_TRUE,SDL_MapRGB(images[image]->surface->s->format,R,G,B));
		}else{
			SDL_SetColorKey(images[image]->surface->s,SDL_FALSE,SDL_MapRGB(images[image]->surface->s->format,R,G,B));
		}
		temp->texture=new Texture(SDL_CreateTextureFromSurface(renderer,images[image]->surface->s));
		if(oldFlag==0){
			SDL_SetColorKey(images[image]->surface->s,SDL_TRUE,colorKey);
		}else{
			SDL_SetColorKey(images[image]->surface->s,SDL_FALSE,colorKey);
		}
		//destroy old Image
		decSurface(images[image]->surface);
		decTexture(images[image]->texture);
		delete images[image];
		//set new image as the one to be used
		images[image] = temp;	
	}
}

void Sprite::setPriority(int pri){//good
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


void Sprite::renderSprites(){//good
	PriList* currentL;
	Sprite* currentS;
	RenderLink* temp = NULL;
	currentL=zero;

	while(currentL!=NULL){
		currentS=currentL->next;
		while(currentS!=NULL){
			if(currentS->vis){
				currentS->animUD();
				SDL_RenderCopyEx(currentS->renderer, currentS->images[currentS->curImage]->texture->t, currentS->srcrect, currentS->dstrect,currentS->angle,currentS->center,currentS->flip); //add textures to the appropriate renderers.
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

void Sprite::addImage(std::string bmp){//good

	if(nextImage<imageCount){
		images[nextImage] = new Image();
		images[nextImage]->surface=new Surface(SDL_LoadBMP(bmp.c_str()));
		images[nextImage]->texture=new Texture(SDL_CreateTextureFromSurface(renderer,images[nextImage]->surface->s));
		images[nextImage]->renderer = renderer;
		nextImage++;
	}

}

void Sprite::addImage(Image* img){//good

	if(nextImage<imageCount){
		if(img->renderer!=renderer){
			images[nextImage] = new Image();
			images[nextImage]->renderer = renderer;
			images[nextImage]->surface = img->surface;
			images[nextImage]->surface->count+=1;
			images[nextImage]->texture=new Texture(SDL_CreateTextureFromSurface(renderer,images[nextImage]->surface->s));
		}else{
			images[nextImage] = img;
			images[nextImage] = new Image();
			images[nextImage]->renderer = renderer;
			images[nextImage]->surface = img->surface;
			images[nextImage]->texture = img->texture;
			img->surface->count+=1;
			img->texture->count+=1;
		}
		nextImage++;
	}

}

Sprite* Sprite::cloneSprite(Sprite* original){//good
	if(original!=NULL){
		Sprite* temp = new Sprite();
		temp->renderer=original->renderer;
		temp->imageCount=original->imageCount;
		temp->images=new Image*[original->imageCount];
		for(int i=0;i<original->imageCount;i++){
			temp->images[i]=new Image();
			temp->images[i]->renderer=original->images[i]->renderer;
			temp->images[i]->surface=original->images[i]->surface;
			temp->images[i]->texture=original->images[i]->texture;
			temp->images[i]->surface->count+=1;
			temp->images[i]->texture->count+=1;
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
		temp->center->x=original->center->x;
		temp->center->y=original->center->y;
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


Sprite* Sprite::cloneSprite(Sprite* original,SDL_Renderer* renderer){//good
	if(original!=NULL){
		Sprite* temp = new Sprite();
		temp->renderer=renderer;
		temp->imageCount=original->imageCount;
		temp->images=new Image*[original->imageCount];
		for(int i=0;i<original->imageCount;i++){
			temp->images[i]=new Image();
			temp->images[i]->renderer=renderer;
			temp->images[i]->surface=original->images[i]->surface;
			temp->images[i]->surface->count+=1;
			temp->images[i]->texture=new Texture(SDL_CreateTextureFromSurface(renderer,temp->images[i]->surface->s));
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


void Sprite::deleteSprite(Sprite* sprite,bool deleteResources){//bad
	if(!deleteResources){
		sprite->clearFromList();
		delete sprite;
	}else{
		sprite->clearFromList();
		for(int i=0;i<sprite->nextImage;i++){//we don't delete renderers...
			SDL_FreeSurface(sprite->images[i]->surface->s);
			SDL_DestroyTexture(sprite->images[i]->texture->t);
			delete (sprite->images[i]);
		}
		delete sprite;
	}

}

Parr* Sprite::rectCol(Sprite* obj){//doesn't check verticies or for angled collisions //good
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

ColState Sprite::autoCol(Sprite* obj){//good
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

void Sprite::animUD(){//good
	if(animate){
		frameCounter++;
		if(frameCounter>=fpf){
			frameCounter=0;
			curImage++;
			if(curImage>endF){
				curImage=startF;
				if(!loop)
					animate=false;
			}
		}
	}
}

void Sprite::moveTo(double x,double y){//good
	double diffx,diffy;
	diffx=X()-x;
	diffy=Y()-y;
	this->x=x;this->y=y;dstrect->x=(int)x;dstrect->y=(int)y;
	SpriteCont* temp = relFirst;
	while(temp!=NULL){
		temp->sprite->moveTo(temp->sprite->X()-diffx,temp->sprite->Y()-diffy);
		temp=temp->next;

	}
	
}

void Sprite::setRelative(Sprite* host,bool sameRotCenter){//good
	this->disableRelative();
	if(host!=NULL){
		SpriteCont* temp;
		temp=host->relFirst;
		host->relFirst=new SpriteCont();
		host->relFirst->next=temp;
		host->relFirst->sprite=this;
		this->host=host;
		if(sameRotCenter){
			this->setRotCenter((int)(host->rotCentX()+(host->X()-x)),(int)(host->rotCentY()+(host->Y()-y)));
		}
	}
}
void Sprite::disableRelative(){//good
	if(host!=NULL){
		SpriteCont* temp,*prev;
		temp=host->relFirst;
		prev=NULL;
		while(temp->sprite!=this){
			prev=temp;
			temp=temp->next;
		}
		if(prev==NULL){
			host->relFirst=temp->next;
			delete temp;
		}else{
			prev->next=temp->next;
			delete temp;
		}
	}
	host=NULL;
}

void Sprite::setAngle(double angle){//good
	double diff = this->angle-angle;
	this->angle=angle;
	SpriteCont* temp = relFirst;
	while(temp!=NULL){
		temp->sprite->setAngle(temp->sprite->getAngle()-diff);
		temp=temp->next;

	}
}

Image* Sprite::loadImage(std::string bmp,SDL_Renderer* renderer){//good
	if(renderer!=NULL){
		Image* temp = new Image();
		temp->surface=new Surface(SDL_LoadBMP(bmp.c_str()));
		temp->texture=new Texture(SDL_CreateTextureFromSurface(renderer,temp->surface->s));
		temp->renderer = renderer;
		temp->texture->user=true;
		temp->surface->user=true;
		return temp;
	}
	return NULL;
}

bool Sprite::setAllAlpaMod(Uint8 alpha){//good
	
	for(int i=0;i<nextImage;i++){
		Image* temp = new Image();
		temp->surface=images[i]->surface;
		images[i]->surface->count+=1;
		temp->renderer=images[i]->renderer;
		temp->texture=new Texture(SDL_CreateTextureFromSurface(temp->renderer,temp->surface->s));
		if(SDL_SetTextureAlphaMod(temp->texture->t,alpha)==0){
			decSurface(images[i]->surface);
			decTexture(images[i]->texture);
			delete images[i];
			
			images[i]=temp;
		}else{
			delete temp;
			return false;
		}
	}

	return true;
}