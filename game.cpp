#include<iostream>
#include<SFML/Graphics.hpp>
#include "Entity.cpp"
#include "ArialFont.hpp"
#include <list>
#include "Collectable.cpp"
#include "Player.cpp"

class game
{

    public:
        game();
        void run();
        const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

        /*changes to entity list to be made
        * make pointer to player and make list of entitys not list of pointers
        * this will reduce code dupication when creating entitys in the future.
        */
        std::list <Entity*> entityList;
    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
    private:
        sf::RenderWindow mWindow;
        Player player;
        Collectable box;
        Entity box2;
        Entity box3;

    public:
        sf::Text text;
        sf::Font font;
        
};

game::game()
    //resoultion 
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, player()
{

    //cap framerate at 60fps5
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

    font.loadFromFile("fonts/arial.ttf");
         text.setFont(font);
         text.setFillColor(sf::Color::Green);
         text.setString("this is a test");
         text.setCharacterSize(24);
  
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
    player.handlePlayerInput(event.key.code, true);
    break;
case sf::Event::KeyReleased:
    player.handlePlayerInput(event.key.code, false);
    break;
case sf::Event::Closed:
    mWindow.close();
    break;

}


}
}




//called every frame
void game::update(sf::Time deltaTime)
{
    //calculate the amount to move the player by per frame
    sf::Vector2f movement(0.f, 0.f);
    

    movement = player.getMovementVector();
    


    //take a none drawn step
    sf::Vector2f prevPos =  sf::Vector2f(player.xPos, player.yPos);
    player.move(movement * deltaTime.asSeconds());            
    std::list<Entity *>::iterator it;
         for (it = entityList.begin(); it != entityList.end(); ++it)
        {
            if(player.name != (*it)->name)
            {
                
                if(!((*it)->checkCollision(&player))){ 
                    //draw the new step
                    player.drawable.setPosition(player.xPos, player.yPos); 



                    //debugging player position and hitbox position
                    /*std::cout << std::to_string(player.drawable.getPosition().x) << std::endl;
                    std::cout << std::to_string(player.drawable.getPosition().y) << std::endl;
                    std::cout << "wall location: " + std::to_string(box.xPos) +"  " + std::to_string(box.yPos) << std::endl;
                    */
                }
                else
                {
                                      
                    //a collision has occured stop the player from moving in the colliding direction
                    //std::cout << "drawable position = " + std::to_string(player.drawable.getPosition().x )<< std::endl;
                    //std::cout << "player position = " + std::to_string(player.xPos )<< std::endl;
                    player.setPos(prevPos);
                    //std::cout << "collision Detected" << std::endl;
                }
            }
        }    
    }


void game::render()
{
    mWindow.clear();
    mWindow.draw(text);
    std::list<Entity*>::iterator it;
    for (it = entityList.begin(); it != entityList.end(); ++it)
        {
            std::cout << (*it)->toggle;
            if ((*it)->toggle)
            {           
            mWindow.draw((*it)->drawable);   
            }    
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