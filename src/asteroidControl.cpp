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

//returns list of positions of bullets that hit asteroids and list of ship points that were hit by asteroid
vector<list<vec2>> asteroidControl::update(list<vec2> s, list<vec2> bullets){
    list<vec2> hits;
    list<vec2> shipHits;
    
    shipPos = s;
    for(asteroid &a: mAsteroids){
        a.update();
        //see what bullets have hit asteroids
        for(vec2 &b: bullets){
            if(a.body.contains(b)){
                a.isHit = true;
                hits.push_back(b);
            }
        }
        //see what ships have collided with asteroids
        for(vec2 &shipPoint: s){
            if(a.body.contains(shipPoint)){
                shipHits.push_back(shipPoint);
            }
        }
    }
    
    //if asteroid is hit,
    //if big then create 2 smalls and erase
    //if small just erase
    for(list<asteroid>::iterator a = mAsteroids.begin() ; a != mAsteroids.end();){
        if(a->isHit){
            if(a->isBig){
                mAsteroids.push_back(asteroid(a->center, false));
                mAsteroids.push_back(asteroid(a->center, false));
            }
            auto deleting = a;
            ++a;
            mAsteroids.erase(deleting);
        }else{
            ++a;
        }
    }
    
    //if all asteroids have been destroyed, repopulate
    if(mAsteroids.begin() == mAsteroids.end()){
        createAsteroids(5);
    }
    
    vector<list<vec2>> shipsBullets;
    shipsBullets.push_back(hits);
    shipsBullets.push_back(shipHits);
    return shipsBullets;
}

void asteroidControl::createAsteroids(int num){
    //randomly place asteroids
    //ensure they are not within radius of ship
    while(num > 0){
        vec2 a = vec2(rand() % getWindowWidth(), rand() % getWindowHeight());
        for(vec2 i: shipPos){
            while(distance(i, a) < 200){
                a = vec2(rand() % getWindowWidth(), rand() % getWindowHeight());
            }
        }
        asteroid as = asteroid(a, true);
        mAsteroids.push_back(as);
        num--;
    }
}

