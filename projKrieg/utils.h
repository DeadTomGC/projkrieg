#pragma once

#include <math.h>
#include "SDL.h"


class Point{
public:
	Point(){}
	Point(int x,int y):x(x),y(y){}
	int x;
	int y;
};
class Parr{
public:
	int pointC;
	Point* arr[8];
	Parr(){
		pointC=0;
		for(int i=0;i<8;i++){
			arr[i] = NULL;
		}
	}
	void add(Point* p){
		if(pointC<8){
			arr[pointC]=p;
			pointC++;
		}
	}
	~Parr(){
		for(int i=0;i<8;i++){
			if(arr[i]!=NULL){
				delete (arr[i]);
			}
		}
	}

};

float min(float i,float j);
float max(float i,float j);

float dist(Point* p1,Point* p2);
Point* intersection(Point p1, Point p2, Point p3, Point p4);