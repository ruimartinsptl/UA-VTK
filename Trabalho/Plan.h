#pragma once
class Plan
{
private:
	double width;
	double height;
public:
	Plan(void);
	Plan(double width, double height);
	~Plan(void);

	double Plan::getWidth(void);
	double Plan::getHeight(void);
	void Plan::setWidth(double width);
	void Plan::setHeight(double height);
};

