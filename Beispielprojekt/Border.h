#pragma once

#ifndef BORDER_H_
#define BORDER_H_

 class  Border 
{
private:
	double uX;
	double lX;
	double uY;
	double LY;
public:
	Border();
	Border(double uXd, double lXd, double uYd, double lYd);
};

#endif // !BORDER_H_