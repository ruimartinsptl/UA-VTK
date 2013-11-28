#include "Point3D.h"

double X=0.00;
double Y=0.00;
double Z=0.00;

Point3D::Point3D(void)
{
	X=0.00;
	Y=0.00;
	Z=0.00;
}

Point3D::Point3D(double X, double Y, double Z){
	this->setX(X);
	this->setY(Y);
	this->setZ(Z);
}


Point3D::~Point3D(void)
{
}

double Point3D::getX(void){
	return X;
}

double Point3D::getY(void){
	return Y;
}

double Point3D::getZ(void){
	return Z;
}

void Point3D::setX(double X){
	Point3D::X=X;
}

void Point3D::setY(double Y){
	Point3D::Y=Y;
}

void Point3D::setZ(double Z){
	Point3D::Z=Z;
}