#include "Plan.h"

double width=0.00;	//Largura
double height=0.00;	//Altura

Plan::Plan(void)
{
}

Plan::Plan(double width, double height)
{
	setWidth(width);
	setHeight(height);
}


Plan::~Plan(void)
{
}

double Plan::getWidth(void){
	return width;
}

double Plan::getHeight(void){
	return height;
}

void Plan::setWidth(double width){
	this->width=width;
}

void Plan::setHeight(double height){
	this->height=height;
}