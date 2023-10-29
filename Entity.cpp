#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


class Entity
{
    public:
     float xPos, yPos;
     float length, height; 
     bool toggle = true;
     std::string name;
     sf::RectangleShape drawable;

    Entity()
    {
     
    };


    void setUp(float xPos, float yPos, float length, float height, std::string name)
    {
        this->xPos = xPos;
        this->yPos = yPos;
        this->height = height;
        this->length = length;
        this->name = name;
        
        drawable.setPosition(xPos, yPos);
        drawable.setSize(sf::Vector2f(length, height));
        drawable.setFillColor(sf::Color::Red);

    
         
    }

    sf::RectangleShape getShape()
    {
        return this->drawable;
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
        std::cout << ("hitBox pos = " + std::to_string(collidableEntity.height) + "," + std::to_string(this->yPos)) << std::endl;
        return
                xPos + length >= collidableEntity.xPos &&
                xPos <= collidableEntity.xPos + collidableEntity.length &&
                yPos + height >= collidableEntity.yPos &&
                yPos <= collidableEntity.yPos + collidableEntity.height;
                

    }

};