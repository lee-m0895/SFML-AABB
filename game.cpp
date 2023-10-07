#include<iostream>
#include<SFML/Graphics.hpp>
#include "Entity.cpp"
#include "ArialFont.hpp"

class game
{

    public:
        game();
        void run();
        bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false , mIsMovingRight = false; 
        const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    private:
        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;
        sf::RectangleShape bounds;
        Entity player;
        Entity box;
        sf::Text debugText;
        sf::Font font;
        
};

game::game()
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, mPlayer(), bounds(), player(), debugText()
{
    sf::Font fromMem;
    fromMem.loadFromMemory(_home_lee_Documents_Game_fonts_arial_ttf, _home_lee_Documents_Game_fonts_arial_ttf_len);
    
    //player draw infolayer.setPosition()
    
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(0.f, 0.f);
    mPlayer.setFillColor(sf::Color::Cyan);
    bounds.setSize(sf::Vector2f(80.f, 80.f));
    bounds.setPosition(100.f, 100.f);
    bounds.setOutlineColor(sf::Color::Red);
    bounds.setOutlineThickness(5);
    player.setUp(0.f, 0.f, 80.f, 80.f);
    box.setUp(100.f, 100.f, 80.f, 80.f);

    debugText.setFont(fromMem);
    debugText.setCharacterSize(24);
    debugText.setFillColor(sf::Color::Red);
    debugText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    debugText.setString("hello");
    std::cout.flush();
    std::cout << "HELLO WORLD!!" << std::endl;
    


    
}


void game::run()
{
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
sf::Event event;
while (mWindow.pollEvent(event))
{
//if (event.type == sf::Event::Closed)
//mWindow.close();

switch (event.type)
{
case sf::Event::KeyPressed:
    handlePlayerInput (event.key.code, true);
    /* code */
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

void game::handlePlayerInput(sf::Keyboard::Key key, bool ispressed)
{
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



void game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        if(!(mPlayer.getPosition().y <= 0.0f))
        {
            
            movement.y -= 100.f;
        }
    if (mIsMovingDown)
        if(!(mPlayer.getPosition().y >= 480.f - mPlayer.getRadius()*2))
        {
            movement.y += 100.f;
        }
        
    if (mIsMovingLeft){
        if(!(mPlayer.getPosition().x <= 0.f ))
        {
            movement.x -= 100.f;
        }
    }
    if (mIsMovingRight)
    {
        if(!(mPlayer.getPosition().x >= 640.f - mPlayer.getRadius()*2))
            {
                movement.x += 100.f;
            }
    }
    //bounds.move(mPlayer.getPosition());
    
    player.move(movement * deltaTime.asSeconds());
    if(!player.checkCollision(box))
    {
        mPlayer.setPosition(player.xPos, player.yPos);
           
    }
    else
    {
        player.setPos(mPlayer.getPosition());
        std::cout << "collision Detected" << std::endl;

    }
    //std::cout << ("hitBox pos = " + std::to_string(player.xPos) + "," + std::to_string(player.yPos)) << std::endl;
    }


void game::render()
{
    mWindow.clear();
    mWindow.draw(bounds);
    mWindow.draw(mPlayer);
    mWindow.display();
}

int main()
{
    game gameTest;
    gameTest.run();
    return 0;
}