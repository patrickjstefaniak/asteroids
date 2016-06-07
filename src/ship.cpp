//
//  ship.cpp
//  asteroids
//
//  Created by Patrick Stefaniak on 6/2/16.
//
//

#include "ship.h"

ship::ship()
{
    forward = vec2(0,-1);
    drag = 1.009;
    lives = 1;
    center = getWindowCenter();
    velocity = vec2(0);
    turning = 0;
    constructBody();
    forwardMotion = 0;
    size = 15;
    score = 0;
    bullets.push_back(bullet(forward, center));
}

ship::ship(vec2 pos)
{
    
}

void ship::draw()
{
    gl::color(1,1,1);
    gl::draw(body);
    for(bullet b: bullets){
        b.draw();
    }
}

void ship::move(KeyEvent event)
{
    switch (event.getCode()) {
        case KeyEvent::KEY_RIGHT:
            turning += 0.1f;
            break;
            
        case KeyEvent::KEY_LEFT:
            turning -= 0.1f;
            break;
            
        case KeyEvent::KEY_UP:
            forwardMotion += 0.8f;
            break;
            
        case KeyEvent::KEY_DOWN:
            forwardMotion -= 0.8f;
            break;
            
        case KeyEvent::KEY_SPACE:
            shoot();
            break;
            
        default:
            break;
    }
}

void ship::update()
{
    //turn ship
    forward = forward * mat2(cos(turning), -sin(turning), sin(turning), cos(turning));
    forward = normalize(forward);
    turning = 0;
    //adjust acceleration
    vec2 newVel = forwardMotion * forward;
    forwardMotion = 0;
    
    //limit max speed
    if(length(velocity) > 3){
        vec2 velDir = normalize(velocity);
        velocity = velDir * 3.0f;
    }
    velocity += newVel;
    if(length(velocity) > 0){
        velocity = velocity / drag;
    }
    //adjust position
    center += velocity;
    
    //check to see if off screen, wrap to other side
    if(center.x < 0){
        center.x = getWindowWidth() + (size / 2);
    }else if(center.x > getWindowWidth() + (size / 2)){
        center.x = 0;
    }
    if(center.y < 0){
        center.y = getWindowHeight() + (size / 2);
    }else if(center.y > getWindowHeight() + (size / 2)){
        center.y = 0;
    }
    constructBody();
    
    for(list<bullet>::iterator b = bullets.begin() ; b != bullets.end();){
        b->update();
        if(! b->isAlive){
            auto deleting = b;
            ++b;
            bullets.erase(deleting);
        }else{
            ++b;
        }
    }
}

void ship::shoot()
{
    bullet b = bullet(forward, center);
    bullets.push_back(b);
}

void ship::hit(list<Shape2d> asteroids){
    for(Shape2d &a: asteroids){
        for(vec2 &p: body.getPoints()){
            if(a.contains(p)){
                die();
            }
        }
            
    }
}

void ship::die()
{
    lives -= 1;
    if(lives <= 0){
        //ship deaaad
        cout << " dead ";
    }
}

void ship::constructBody()
{
    body.clear();
    body.moveTo(center + (forward * size));
    vec2 perp = mat2(0, -1, 1, 0) * forward;
    body.lineTo(center + (perp * size / 3.0f));
    body.lineTo(center - (perp * size / 3.0f));
    body.close();
}