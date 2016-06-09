#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ship.h"
#include "asteroidControl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class asteroidsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
    
    list<vec2> getShipsPos();
    list<vec2> getBulletsPos();
    
    ship            p1;
    vector<ship>    ships;
    asteroidControl ac;
};

void asteroidsApp::setup()
{
    setWindowSize(800, 600);
    p1 = ship();
    ac = asteroidControl(getShipsPos());
    ships.push_back(p1);
}

void asteroidsApp::mouseDown( MouseEvent event )
{
    //cout << p1.center << "   ";
}

void asteroidsApp::keyDown(KeyEvent event)
{
    p1.move(event);
}

void asteroidsApp::update()
{
    p1.update();
    ac.update(getShipsPos(), getBulletsPos());
}

void asteroidsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    p1.draw();
    ac.draw();
}

list<vec2> asteroidsApp::getShipsPos(){
    list<vec2> r;
    r.push_back(p1.center);
    return r;
}

list<vec2> asteroidsApp::getBulletsPos(){
    list<vec2> b;
    for(ship &s: ships){
        b.push_back(s.getBullets());
        //cout << s.getBullets();
    }
    return b;
}

CINDER_APP( asteroidsApp, RendererGl )
