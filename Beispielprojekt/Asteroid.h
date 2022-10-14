#pragma once
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Schuss.h"

using namespace std;

struct Asteorid {
    const int AsteroidHoehe = 40;
    const int AsteroidBreite = 50;
    const int AsteroidPos = 1;
    const Gosu::Color AsteroidFarbe = Gosu::Color::NONE;
    double AsteroidY;
    double AsteroidX;
    bool hit = false;

};

void erstelleAsteroid(vector<Asteorid>& AstVect) {
    double x = Gosu::random(30, 970);
    Asteorid ast;
    ast.AsteroidY = 0;
    ast.AsteroidX = x;
    AstVect.push_back(ast);
}

