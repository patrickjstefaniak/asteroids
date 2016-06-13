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
    TextBox         scoreBoard, title, spaceContinue;
    bool            gameOver, startScreen;
    bool            buttonsDown[4][5];
    int             bulletDelay, menuDelay, numPlayers;
};

void asteroidsApp::setup()
{
    setWindowSize(800, 600);
    p1 = ship();
    ships.push_back(p1);
    ac = asteroidControl(getShipsPos());
    spaceContinue = TextBox().font(Font("Courier" , 30)).size(vec2(getWindowWidth(), 50)).alignment(TextBox::CENTER);
    scoreBoard = TextBox().font(Font("Courier", 20)).size(vec2(getWindowWidth()/4, 50));
    title = TextBox().font(Font("Courier", 70)).size(vec2(getWindowWidth(),100)).alignment(TextBox::CENTER);
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 5; y++){
            buttonsDown[x][y] = false;
        }
    }
    bulletDelay = 0;
    menuDelay = 0;
    startScreen = true;
    gameOver = false;
    numPlayers = 1;
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
            
        case KeyEvent::KEY_d:
            buttonsDown[0] = true;
            break;
            
        case KeyEvent::KEY_a:
            buttonsDown[1] = true;
            break;
            
        case KeyEvent::KEY_w:
            buttonsDown[2] = true;
            break;
            
        case KeyEvent::KEY_s:
            buttonsDown[3] = true;
            break;
            
        case KeyEvent::KEY_e:
            buttonsDown[4] = true;
            break;
            
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
    if(!startScreen && !gameOver){
        //to prevent from being able to hold down button and create lots of bullets
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
        //see if ship is hit by asteroid
        for(vec2 &h : hits.back()){
            if(p1.invincible <= 0){
                if(p1.lives == 0){
                    gameOver = true;
                    menuDelay = 100;
                }
                //a not very effective way of stopping ship from moving after respawning
                for(bool &button: buttonsDown){
                    button = false;
                }
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
    }else{
        menuDelay --;
        if(buttonsDown[4] && menuDelay <= 0){
            if(startScreen){
                startScreen = false;
                buttonsDown[4] = false;
            }else if(gameOver){
                gameOver = false;
                startScreen = true;
                ships.clear();
                bullets.clear();
                p1 = ship();
                ships.push_back(p1);
                ac = asteroidControl(getShipsPos());
                buttonsDown[4] = false;
                menuDelay = 100;
            }
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
    if(startScreen){
        title.text("a s t e r o i d s");
        gl::pushMatrices();
        gl::translate(vec2(0,getWindowHeight()/3 + 50));
        gl::draw(gl::Texture2d::create(title.render()));
        gl::translate(vec2(0,100));
        spaceContinue.text("----press space to start----");
        gl::draw(gl::Texture2d::create(spaceContinue.render()));
        gl::popMatrices();
    }
    if(gameOver){
        title.text("g a m e   o v e r");
        gl::pushMatrices();
        gl::translate(vec2(0,getWindowHeight()/3 + 50));
        gl::draw(gl::Texture2d::create(title.render()));
        gl::translate(vec2(0,100));
        spaceContinue.text("----press space to continue----");
        gl::draw(gl::Texture2d::create(spaceContinue.render()));
        gl::popMatrices();
    }
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
