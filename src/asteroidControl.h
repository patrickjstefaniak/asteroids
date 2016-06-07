//
//  asteroidControl.h
//  asteroids
//
//  Created by Patrick Stefaniak on 6/7/16.
//
//

#include "asteroid.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#pragma once

class asteroidControl {
public:
    asteroidControl(){};
    asteroidControl(list<vec2> s);
    
    void draw();
    void update(list<vec2> s, list<vec2> bullets);
    void createAsteroids(int num);
    
    list<asteroid> mAsteroids;
    list<vec2>      shipPos;
    
};
