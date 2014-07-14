#include "utils.h"

float min(float i,float j){return (i<j)?i:j;}
float max(float i,float j){return (i>j)?i:j;}

float dist(Point* p1,Point* p2){
	return sqrt(pow((float)((p1->x)-(p2->x)),2)+pow((float)((p1->y)-(p2->y)),2));
}


Point* intersection(Point p1, Point p2, Point p3, Point p4) {
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = (float)p1.x, x2 = (float)p2.x, x3 = (float)p3.x, x4 = (float)p4.x;
	float y1 = (float)p1.y, y2 = (float)p2.y, y3 = (float)p3.y, y4 = (float)p4.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return NULL;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

	// Check if the x and y coordinates are within both lines
	if ( x < min(x1, x2) || x > max(x1, x2) ||
		x < min(x3, x4) || x > max(x3, x4) ) return NULL;
	if ( y < min(y1, y2) || y > max(y1, y2) ||
		y < min(y3, y4) || y > max(y3, y4) ) return NULL;

	// Return the point of intersection
	Point* ret = new Point();
	ret->x = (int)x;
	ret->y = (int)y;
	return ret;
}