
#include "Sprite.h"
#include "SDL.h"

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
			SDL_RenderCopy(currentS->renderer, currentS->images[currentS->curImage]->texture, currentS->srcrect, currentS->dstrect); //add textures to the appropriate renderers.
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
			currentS=currentS->next;
		}
		currentL=currentL->nextHigher;
	}
	RenderLink* current = temp;
	while(current!=NULL){//render all frames
		SDL_RenderPresent(current->rend);
		current = current->next;
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