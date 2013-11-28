#pragma once
class Point3D
{
private:
	double X;
	double Y;
	double Z;
public:
	Point3D(void);
	Point3D(double X, double Y, double Z);
	~Point3D(void);

	double Point3D::getX(void);
	double Point3D::getY(void);
	double Point3D::getZ(void);
	void Point3D::setX(double X);
	void Point3D::setY(double Y);
	void Point3D::setZ(double Z);
	
};

