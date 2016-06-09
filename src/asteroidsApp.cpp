#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ship.h"
#include "asteroidControl.h"
#include "bullet.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class asteroidsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;
	void update() override;
	void draw() override;
    
    list<vec2> getShipsPos();
    list<vec2> getBulletsPos();
    
    ship            p1;
    vector<ship>    ships;
    list<bullet>    bullets;
    asteroidControl ac;
    TextBox         scoreBoard;
    bool            buttonsDown[5];
    int             bulletDelay;
};

void asteroidsApp::setup()
{
    setWindowSize(800, 600);
    p1 = ship();
    ac = asteroidControl(getShipsPos());
    ships.push_back(p1);
    scoreBoard = TextBox().font(Font("Courier", 20)).size(vec2(getWindowWidth()/4, 50));
    for(bool &b: buttonsDown){
        b = false;
    }
    bulletDelay = 0;
}

void asteroidsApp::mouseDown( MouseEvent event )
{
    //cout << p1.center << "   ";
}

//keys:
//0 = right
//1 = left
//2 = up
//3 = down
//4 = space

void asteroidsApp::keyDown(KeyEvent event)
{
    switch (event.getCode()) {
        case KeyEvent::KEY_RIGHT:
            buttonsDown[0] = true;
            break;
            
        case KeyEvent::KEY_LEFT:
            buttonsDown[1] = true;
            break;
            
        case KeyEvent::KEY_UP:
            buttonsDown[2] = true;
            break;
            
        case KeyEvent::KEY_DOWN:
            buttonsDown[3] = true;
            break;
            
        case KeyEvent::KEY_SPACE:
            buttonsDown[4] = true;
            break;
            
        default:
            break;
    }
}

void asteroidsApp::keyUp(KeyEvent event){
    switch (event.getCode()) {
        case KeyEvent::KEY_RIGHT:
            buttonsDown[0] = false;
            break;
            
        case KeyEvent::KEY_LEFT:
            buttonsDown[1] = false;
            break;
            
        case KeyEvent::KEY_UP:
            buttonsDown[2] = false;
            break;
            
        case KeyEvent::KEY_DOWN:
            buttonsDown[3] = false;
            break;
            
        case KeyEvent::KEY_SPACE:
            buttonsDown[4] = false;
            break;
            
        default:
            break;
    }
}

void asteroidsApp::update()
{
    if(bulletDelay > 0){
        bulletDelay --;
    }
    
    p1.move(buttonsDown);
    if(buttonsDown[4] && bulletDelay <= 0){
        bullet b = bullet(p1);
        bullets.push_back(b);
        bulletDelay = 50;
    }else if(!buttonsDown[4]){
        bulletDelay = 0;
    }
    p1.update();
    ac.shipPos = getShipsPos();
    
    //see if any asteroids were hit
    //ac.update returns list of asteroids hit by bullets
    //and list of ships hit by asteroids respectively
    auto hits = ac.update(getShipsPos(), getBulletsPos());
    for(vec2 &h : hits.front()){
        for(bullet &b: bullets){
            if(b.pos == h){
                b.hit();
            }
        }
    }
    //see if ship is hit
    for(vec2 &h : hits.back()){
        if(p1.body.contains(h)){
            p1.die();
        }
    }
    
    //update bullets
    for(list<bullet>::iterator b = bullets.begin(); b!=bullets.end();){
        b->update();
        if(!b->isAlive){
            auto c = b;
            ++b;
            bullets.erase(c);
        }else{
            ++b;
        }
    }
}

void asteroidsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    p1.draw();
    ac.draw();
    for(bullet &b: bullets){
        b.draw();
    }
    gl::pushMatrices();
    scoreBoard.text("lives: " + to_string(p1.lives)).alignment(TextBox::LEFT);
    gl::translate(vec2(getWindowWidth()/4,0));
    gl::draw(gl::Texture2d::create(scoreBoard.render()));
    gl::translate(vec2(getWindowWidth()/4,0));
    scoreBoard.text("score: " + to_string(p1.score)).alignment(TextBox::RIGHT);
    gl::draw(gl::Texture2d::create(scoreBoard.render()));
    gl::popMatrices();
}

list<vec2> asteroidsApp::getShipsPos(){
    list<vec2> r;
    vector<vec2> points = p1.body.getPoints();
    for(vec2 p: points){
        r.push_back(p);
    }
    return r;
}

list<vec2> asteroidsApp::getBulletsPos(){
    list<vec2> buls;
    for(bullet &b : bullets){
        buls.push_back(b.pos);
    }
    return buls;
}

CINDER_APP( asteroidsApp, RendererGl )
