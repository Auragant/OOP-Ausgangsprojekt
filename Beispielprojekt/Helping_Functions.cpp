/*****************************************************************//**
 * \file   Helping_Functions.cpp
 * \brief  Just some helping functions
 * 
 * \author Jan
 * \date   October 2022
 *********************************************************************/

#include "Helping_Functions.h"
#include <algorithm>

using namespace std;

double max3(auto a, auto b, auto c)
{
	double ret = max(a, b);
	ret = max(ret, c);

	return ret;
}

double min3(auto a, auto b, auto c)
{
	double ret = min(a, b);
	ret = min(ret, c);

	return ret;
}