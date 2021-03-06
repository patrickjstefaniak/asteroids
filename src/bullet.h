//
//  bullet.h
//  asteroids
//
//  Created by Patrick Stefaniak on 6/7/16.
//
//

#include "ship.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#pragma once

class bullet {
public:
    bullet();
    bullet(vec2 dir, vec2 pos);
    bullet(ship &s);
    
    void update();
    void draw();
    void hit();
    
    vec2    pos, direction;
    int     lifeSpan;
    bool    isAlive;
    ship    *shotFrom;
};