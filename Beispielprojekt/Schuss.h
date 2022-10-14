#pragma once
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Asteroid.h"

using namespace std;

struct Schuss
{
    const int SchussBreite = 3;
    const int SchussHoehe = 10;
    const int SchussPos = 1;
    const Gosu::Color SchussFarbe = Gosu::Color::RED;
    double SchussY;
    double SchussX;
    bool existent = true;
};


Schuss erstelleSchuss(double x, double y) 
{
    Schuss st;
    st.SchussY = y;
    st.SchussX = x;
    return st;

}