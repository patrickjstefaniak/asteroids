//
//  bullet.h
//  asteroids
//
//  Created by Patrick Stefaniak on 6/7/16.
//
//

using namespace ci;
using namespace ci::app;
using namespace std;

#pragma once

class bullet {
public:
    bullet();
    bullet(vec2 dir, vec2 pos);
    
    void update();
    void draw();
    
    vec2    pos, direction;
    int     lifeSpan;
    bool    isAlive;
};