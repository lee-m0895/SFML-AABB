#include "Entity.h"
#include "SFML/Graphics.hpp"
class Player : public Entity
{
    private:

    public:
    int score;
    int health;
    bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false , mIsMovingRight = false; 

    
    void handlePlayerInput(sf::Keyboard::Key key, bool ispressed)
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


    sf::Vector2f getMovementVector()
    {
         //calculate the amount to move the player by per frame
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        //check if in level bounds ceiling
        if(!(drawable.getPosition().y <= 0.0f))
        {
            
            movement.y -= 100.f;
        }
        
    if (mIsMovingDown)
        //floor
        if(!(drawable.getPosition().y >= 480.f - height))
        {
            movement.y += 100.f;
        }
        
    if (mIsMovingLeft){
        //left wall
        if(!(drawable.getPosition().x < 0.f ))
        {
            movement.x -= 100.f;
        }
    }
    if (mIsMovingRight)
    {
        //right wall
        if(!(drawable.getPosition().x >= 640.f - length))
            {
                movement.x += 100.f;
            }
    }

    return movement;
    }

};