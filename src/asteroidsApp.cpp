#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ship.h"

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
    
    ship    p1;
};

void asteroidsApp::setup()
{
    setWindowSize(800, 600);
    p1 = ship();
}

void asteroidsApp::mouseDown( MouseEvent event )
{
    cout << p1.center << "   ";
}

void asteroidsApp::keyDown(KeyEvent event)
{
    p1.move(event);
}

void asteroidsApp::update()
{
    p1.update();
}

void asteroidsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    p1.draw();
}

CINDER_APP( asteroidsApp, RendererGl )
