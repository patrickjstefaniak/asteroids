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
    void drawInterface();
    
    list<vec2> getShipsPos();
    list<vec2> getBulletsPos();
    
    ship            ships[4];
    list<bullet>    bullets;
    asteroidControl ac;
    TextBox         scoreBoard, title, spaceContinue;
    bool            gameOver, startScreen;
    bool            buttonsDown[4][5];
    int             menuDelay, numPlayers;
};

void asteroidsApp::setup()
{
    setWindowSize(800, 600);
    ac = asteroidControl(getShipsPos());
    spaceContinue = TextBox().font(Font("Courier" , 30)).size(vec2(getWindowWidth(), 50)).alignment(TextBox::CENTER);
    scoreBoard = TextBox().font(Font("Courier", 20)).size(vec2(getWindowWidth()/4, 50));
    title = TextBox().font(Font("Courier", 70)).size(vec2(getWindowWidth(),100)).alignment(TextBox::CENTER);
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 5; y++){
            buttonsDown[x][y] = false;
        }
    }
    menuDelay = 0;
    startScreen = true;
    gameOver = false;
    numPlayers = 1;
}

void asteroidsApp::mouseDown( MouseEvent event )
{
    //cout << p1.center << "   ";
}

//keys:  p1   p2  p3  p4
//0 = right | d | h | l
//1 = left  | a | f | j
//2 = up    | w | t | i
//3 = down  | s | g | k
//4 = space | e | y | o

void asteroidsApp::keyDown(KeyEvent event)
{
    switch (event.getCode()) {
            //p1
        case KeyEvent::KEY_RIGHT:
            buttonsDown[0][0] = true;
            break;
            
        case KeyEvent::KEY_LEFT:
            buttonsDown[0][1] = true;
            break;
            
        case KeyEvent::KEY_UP:
            buttonsDown[0][2] = true;
            break;
            
        case KeyEvent::KEY_DOWN:
            buttonsDown[0][3] = true;
            break;
            
        case KeyEvent::KEY_SPACE:
            buttonsDown[0][4] = true;
            break;
            
            //p2
        case KeyEvent::KEY_d:
            buttonsDown[1][0] = true;
            break;
            
        case KeyEvent::KEY_a:
            buttonsDown[1][1] = true;
            break;
            
        case KeyEvent::KEY_w:
            buttonsDown[1][2] = true;
            break;
            
        case KeyEvent::KEY_s:
            buttonsDown[1][3] = true;
            break;
            
        case KeyEvent::KEY_e:
            buttonsDown[1][4] = true;
            break;
            
            //p3
        case KeyEvent::KEY_h:
            buttonsDown[2][0] = true;
            break;
            
        case KeyEvent::KEY_f:
            buttonsDown[2][1] = true;
            break;
            
        case KeyEvent::KEY_t:
            buttonsDown[2][2] = true;
            break;
            
        case KeyEvent::KEY_g:
            buttonsDown[2][3] = true;
            break;
            
        case KeyEvent::KEY_y:
            buttonsDown[2][4] = true;
            break;
            
            //p4
        case KeyEvent::KEY_l:
            buttonsDown[3][0] = true;
            break;
            
        case KeyEvent::KEY_j:
            buttonsDown[3][1] = true;
            break;
            
        case KeyEvent::KEY_i:
            buttonsDown[3][2] = true;
            break;
            
        case KeyEvent::KEY_k:
            buttonsDown[3][3] = true;
            break;
            
        case KeyEvent::KEY_o:
            buttonsDown[3][4] = true;
            break;
            
            
        default:
            break;
    }
}

void asteroidsApp::keyUp(KeyEvent event){
    switch (event.getCode()) {
            //p1
        case KeyEvent::KEY_RIGHT:
            buttonsDown[0][0] = false;
            break;
            
        case KeyEvent::KEY_LEFT:
            buttonsDown[0][1] = false;
            break;
            
        case KeyEvent::KEY_UP:
            buttonsDown[0][2] = false;
            break;
            
        case KeyEvent::KEY_DOWN:
            buttonsDown[0][3] = false;
            break;
            
        case KeyEvent::KEY_SPACE:
            buttonsDown[0][4] = false;
            break;
            
            //p2
        case KeyEvent::KEY_d:
            buttonsDown[1][0] = false;
            break;
            
        case KeyEvent::KEY_a:
            buttonsDown[1][1] = false;
            break;
            
        case KeyEvent::KEY_w:
            buttonsDown[1][2] = false;
            break;
            
        case KeyEvent::KEY_s:
            buttonsDown[1][3] = false;
            break;
            
        case KeyEvent::KEY_e:
            buttonsDown[1][4] = false;
            break;
            
            //p3
        case KeyEvent::KEY_h:
            buttonsDown[2][0] = false;
            break;
            
        case KeyEvent::KEY_f:
            buttonsDown[2][1] = false;
            break;
            
        case KeyEvent::KEY_t:
            buttonsDown[2][2] = false;
            break;
            
        case KeyEvent::KEY_g:
            buttonsDown[2][3] = false;
            break;
            
        case KeyEvent::KEY_y:
            buttonsDown[2][4] = false;
            break;
            
            //p4
        case KeyEvent::KEY_l:
            buttonsDown[3][0] = false;
            break;
            
        case KeyEvent::KEY_j:
            buttonsDown[3][1] = false;
            break;
            
        case KeyEvent::KEY_i:
            buttonsDown[3][2] = false;
            break;
            
        case KeyEvent::KEY_k:
            buttonsDown[3][3] = false;
            break;
            
        case KeyEvent::KEY_o:
            buttonsDown[3][4] = false;
            break;
            
        default:
            break;
    }
}

void asteroidsApp::update()
{
    if(!startScreen && !gameOver){
        
    
        for(int i = 0; i < numPlayers; i++){
            ships[i].move(buttonsDown[i]);
        }
        
        //bulletDelay to prevent from being able to hold down button and create lots of bullets
        for(int i = 0; i < numPlayers; i++){
            if(ships[i].bulletDelay < 0){
                ships[i].bulletDelay --;
            }
            if(buttonsDown[i][0] && ships[i].bulletDelay <= 0){
                bullet b = bullet(ships[i]);
                bullets.push_back(b);
                ships[i].bulletDelay = 50;
            }else if(!buttonsDown[i][4]){
                ships[i].bulletDelay = 0;
            }
        }
        
        
        for(int i = 0; i < numPlayers; i++){
            ships[i].update();
        }
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
            for(int i = 0; i < numPlayers; i++){
                if(ships[i].invincible <= 0 && ships[i].body.contains(h)){
                    if(ships[i].lives == 0){
                        ships[i].isActive = false;
                        //see if game over
                        if(!ships[0].isActive && !ships[1].isActive && !ships[2].isActive && !ships[3].isActive){
                            gameOver = true;
                        }
                    }
                    ships[i].die();
                }
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
        //menu interface
        menuDelay --;
        if(buttonsDown[0][4] && menuDelay <= 0){
            if(startScreen){
                startScreen = false;
                buttonsDown[0][4] = false;
                for(int i = 0; i <numPlayers; i++){
                    ships[i] = ship();
                }
            }else if(gameOver){
                gameOver = false;
                startScreen = true;
                bullets.clear();
                ac = asteroidControl(getShipsPos());
                buttonsDown[0][4] = false;
                menuDelay = 100;
                numPlayers = 1;
            }
        }
        if(startScreen){
            if(buttonsDown[0][2]){
                numPlayers ++;
                if(numPlayers > 4){
                    numPlayers = 1;
                }
                buttonsDown[0][2] = false;
            }else if(buttonsDown[0][3]){
                numPlayers --;
                if(numPlayers < 1){
                    numPlayers = 4;
                }
                buttonsDown[0][3] = false;
            }
        }
    }
}

void asteroidsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    for(int i = 0; i < numPlayers; i++){
        ships[i].draw();
    }
    ac.draw();
    for(bullet &b: bullets){
        b.draw();
    }
    drawInterface();
}

list<vec2> asteroidsApp::getShipsPos()
{
    list<vec2> r;
    
    for(int i = 0; i < numPlayers; i++){
        vector<vec2> points = ships[i].body.getPoints();
        for(vec2 p: points){
            r.push_back(p);
        }
    }

    return r;
}

list<vec2> asteroidsApp::getBulletsPos()
{
    list<vec2> buls;
    for(bullet &b : bullets){
        buls.push_back(b.pos);
    }
    return buls;
}

void asteroidsApp::drawInterface()
{
    if(!startScreen && !gameOver){
        gl::pushMatrices();
        scoreBoard.text("lives: " + to_string(ships[0].lives)).alignment(TextBox::LEFT);
        gl::translate(vec2(getWindowWidth()/4,0));
        gl::draw(gl::Texture2d::create(scoreBoard.render()));
        gl::translate(vec2(getWindowWidth()/4,0));
        scoreBoard.text("score: " + to_string(ships[0].score)).alignment(TextBox::RIGHT);
        gl::draw(gl::Texture2d::create(scoreBoard.render()));
        gl::popMatrices();
    }else if(startScreen){
        title.text("a s t e r o i d s");
        gl::pushMatrices();
        gl::translate(vec2(0,getWindowHeight()/4 + 50));
        gl::draw(gl::Texture2d::create(title.render()));
        gl::translate(vec2(0,150));
        spaceContinue.text("players: " + to_string(numPlayers));
        gl::draw(gl::Texture2d::create(spaceContinue.render()));
        gl::translate(vec2(0,100));
        if(menuDelay <= 0){
            spaceContinue.text("----press space to start----");
            gl::draw(gl::Texture2d::create(spaceContinue.render()));
        }
        gl::popMatrices();
    }else if(gameOver){
        title.text("g a m e   o v e r");
        gl::pushMatrices();
        gl::translate(vec2(0,getWindowHeight()/3 + 50));
        gl::draw(gl::Texture2d::create(title.render()));
        gl::translate(vec2(0,100));
        if(menuDelay <= 0){
            spaceContinue.text("----press space to continue----");
            gl::draw(gl::Texture2d::create(spaceContinue.render()));
        }
        gl::popMatrices();
    }

    
}

CINDER_APP( asteroidsApp, RendererGl(RendererGl::Options().msaa(4)))
