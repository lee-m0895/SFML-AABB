#include "Entity.h"
#include "SFML/Graphics.hpp"
#pragma once
class Player : public Entity
{
    private:

    public:
    int score = 0;
    int health;
    bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false , mIsMovingRight = false; 
    void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    sf::Vector2f getMovementVector();

};
