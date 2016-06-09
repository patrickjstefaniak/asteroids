//
//  bullet.cpp
//  asteroids
//
//  Created by Patrick Stefaniak on 6/7/16.
//
//

#include "bullet.h"

bullet::bullet(){
}

bullet::bullet(vec2 dir, vec2 p){
    direction = dir;
    pos = p;
    lifeSpan = 100;
    isAlive = true;
}

bullet::bullet(ship &s){
    shotFrom = &s;
    direction = s.forward;
    pos = s.center;
    //length of bullets travel without hitting anything 
    lifeSpan = 60;
    isAlive = true;
}

void bullet::draw(){
    gl::color(1,1,1);
    gl::drawSolidRect(Rectf(pos-vec2(2), pos+vec2(2)));
}

void bullet::update(){
    if(isAlive){
        pos += direction * 8.0f;
        lifeSpan -= 1;
        if(lifeSpan <= 0){
            isAlive = false;
        }
        if(pos.x < 0){
            pos.x = getWindowWidth();
        }else if(pos.x > getWindowWidth()){
            pos.x = 0;
        }
        if(pos.y < 0){
            pos.y = getWindowHeight();
        }else if(pos.y > getWindowHeight()){
            pos.y = 0;
        }
    }
}

void bullet::hit(){
    //move off screen until removed 
    pos = vec2(100000);
    shotFrom->hit();
    isAlive = false;
}