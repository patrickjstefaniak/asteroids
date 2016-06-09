//
//  asteroidControl.cpp
//  asteroid
//
//  Created by Patrick Stefaniak on 6/7/16.
//
//

#include "asteroidControl.h"

asteroidControl::asteroidControl(list<vec2> s){
    shipPos = s;
    createAsteroids(5);
}



void asteroidControl::draw(){
    for(asteroid &a: mAsteroids){
        a.draw();
    }
}

void asteroidControl::update(list<vec2> s, list<vec2> bullets){
    shipPos = s;
    for(asteroid &a: mAsteroids){
        a.update();
        for(vec2 &b: bullets){
            if(a.body.contains(b)){
                a.isHit = true;
                cout << " hit! at " << b;
            }
        }
    }
    
    for(list<asteroid>::iterator a = mAsteroids.begin() ; a != mAsteroids.end();){
        if(a->isHit){
            auto deleting = a;
            ++a;
            mAsteroids.erase(deleting);
        }else{
            ++a;
        }
    }
}

void asteroidControl::createAsteroids(int num){
    while(num > 0){
        vec2 a = vec2(rand() % getWindowWidth(), rand() % getWindowHeight());
        for(vec2 i: shipPos){
            while(distance(i, a) < 50){
                a = vec2(rand() % getWindowWidth(), rand() % getWindowHeight());
            }
        }
        asteroid as = asteroid(a, true);
        mAsteroids.push_back(as);
        num--;
    }
}

