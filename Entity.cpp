#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{
    public:
     float xPos, yPos;
     float length, height; 

    Entity()
    {
     
    };


    void setUp(float xPos, float yPos, float length, float height)
    {
        this->xPos = xPos;
        this->yPos = yPos;
        this->height = height;
        this->length = length;
    }


    void move(sf::Vector2f newPos)
    {
        this->xPos += newPos.x;
        this->yPos += newPos.y;

    }

    void setPos(sf::Vector2f newPos)
    {
        this->xPos = newPos.x;
        this->yPos = newPos.y;
    }

    bool checkCollision(Entity collidableEntity)
    {
        std::cout << ("hitBox pos = " + std::to_string(this->xPos) + "," + std::to_string(this->yPos)) << std::endl;
        
        return this->xPos + this->length >= collidableEntity.xPos &&
        this->xPos <= collidableEntity.xPos + collidableEntity.length &&
        this->yPos + this->height >= collidableEntity.yPos &&
        this->yPos <= collidableEntity.yPos + collidableEntity.height;
        
    };



};
