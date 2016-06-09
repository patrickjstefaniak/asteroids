//
//  ship.h
//  asteroids
//
//  Created by Patrick Stefaniak on 6/2/16.
//
//


using namespace ci;
using namespace ci::app;
using namespace std;

#pragma once

class ship {
public:
    ship();
    ship(vec2 pos);
    
    void        draw();
    void        move(bool buttons[]);
    void        update();
    void        hit();
    void        die();
    void        constructBody();
    
    //forward is normalized vec of way ship is pointing
    vec2            velocity, forward , center ;
    Path2d          body;
    float           drag, turning, forwardMotion, size;
    int             lives, score;
};