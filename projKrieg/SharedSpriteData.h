#pragma once
#include "core.h"


class SharedSpriteData{
public:
	int framesToAverage;
	double fps, targetfps; //current fps and target fps which is how many fps the programmer should count on getting when moving sprites around
	PriList* zero;//the lowest priority that starts at 0 but may not remain there
	SDL_Renderer* defaultRenderer;//the default renderer
	SDL_Window* defaultWindow;//the default window
	SharedSpriteData(){
		zero = NULL;
		defaultRenderer = NULL;
		defaultWindow = NULL;
		framesToAverage = 10;
		fps = 60;
		targetfps = 60;
	}

};