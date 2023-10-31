#include<iostream>
#include<SFML/Graphics.hpp>
#include "Entity.cpp"
#include "ArialFont.hpp"
#include <list>

class game
{

    public:
        game();
        void run();
        bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false , mIsMovingRight = false; 
        const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
        std::list <Entity*> entityList;
    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    private:
        sf::RenderWindow mWindow;
        Entity player;
        Entity box;
        Entity box2;
        Entity box3;
        
};

game::game()
    //resoultion 
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, player()
{

    //cap framerate at 60fps
    mWindow.setFramerateLimit(60);
    
    //player draw infolayer.setPosition()
    
    player.setUp(0.f, 0.f, 80.f, 80.f, "player");
    box.setUp(100.f, 100.f, 80.f, 80.f, "wall");
    box2.setUp(250.f, 150.f, 80.f, 80.f, "wall");
    box3.setUp(300.f, 300.f, 80.f, 80.f, "wall");
    //add entitys to a list
    entityList.push_back(&player);
    entityList.push_back(&box);
    entityList.push_back(&box2);
    entityList.push_back(&box3);
  
}


void game::run()
{
    // main internal loop. this function handles the
    // calls for updating the game and rendering to the screen.
    sf::Clock clock;
    sf::Time timeSinceLatsUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        timeSinceLatsUpdate += clock.restart();
        
        while (timeSinceLatsUpdate > TimePerFrame)
        {
            timeSinceLatsUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        
        
        render();
    }
    
}


void game::processEvents()
{
    //event handler
sf::Event event;
while (mWindow.pollEvent(event))
{

switch (event.type)
{
case sf::Event::KeyPressed:
    handlePlayerInput (event.key.code, true);
    break;
case sf::Event::KeyReleased:
    handlePlayerInput(event.key.code, false);
    break;
case sf::Event::Closed:
    mWindow.close();
    break;

}


}
}


//keyboard input based code goes here
void game::handlePlayerInput(sf::Keyboard::Key key, bool ispressed)
{
    //toggle player inputs using keyboard presses WASD
    switch (key)
    {
    case sf::Keyboard::W:
    mIsMovingUp = ispressed;
        break;
    case sf::Keyboard::A:
    mIsMovingLeft = ispressed;
        break;
    case sf::Keyboard::S:
    mIsMovingDown = ispressed;
        break;
    case sf::Keyboard::D:    
    mIsMovingRight = ispressed;
    break;
    }
    
}


//called every frame
void game::update(sf::Time deltaTime)
{
    //calculate the amount to move the player by per frame
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        //check if in level bounds ceiling
        if(!(player.drawable.getPosition().y <= 0.0f))
        {
            
            movement.y -= 100.f;
        }
        
    if (mIsMovingDown)
        //floor
        if(!(player.drawable.getPosition().y >= 480.f - player.height))
        {
            movement.y += 100.f;
        }
        
    if (mIsMovingLeft){
        //left wall
        if(!(player.drawable.getPosition().x < 0.f ))
        {
            movement.x -= 100.f;
        }
    }
    if (mIsMovingRight)
    {
        //right wall
        if(!(player.drawable.getPosition().x >= 640.f - player.length))
            {
                movement.x += 100.f;
            }
    }
    
    


    //take a none drawn step
    sf::Vector2f prevPos =  sf::Vector2f(player.xPos, player.yPos);
    player.move(movement * deltaTime.asSeconds());            
    std::list<Entity *>::iterator it;
         for (it = entityList.begin(); it != entityList.end(); ++it)
        {
            if(player.name != (*it)->name)
            {
                if(!player.checkCollision((*it))){ 
                    //draw the new step
                    player.drawable.setPosition(player.xPos, player.yPos);           
                    //debugging player position and hitbox position
                    std::cout << std::to_string(player.drawable.getPosition().x) << std::endl;
                    std::cout << std::to_string(player.drawable.getPosition().y) << std::endl;
                    std::cout << "wall location: " + std::to_string(box.xPos) +"  " + std::to_string(box.yPos) << std::endl;
                }
                else{   
                    //a collision has occured stop the player from moving in the colliding direction
                    std::cout << "drawable position = " + std::to_string(player.drawable.getPosition().x )<< std::endl;
                    std::cout << "player position = " + std::to_string(player.xPos )<< std::endl;

                    player.setPos(prevPos);
                    std::cout << "collision Detected" << std::endl;
                }
            }
        }    
    }


void game::render()
{
    mWindow.clear();

    std::list<Entity*>::iterator it;
    for (it = entityList.begin(); it != entityList.end(); ++it)
        {
        mWindow.draw((*it)->drawable);       
        }

    //mWindow.draw(player.drawable);
    //mWindow.draw(box.drawable);
    mWindow.display();
}

int main()
{
    game gameTest;
    gameTest.run();
    return 0;
}