#pragma once
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
     virtual bool checkCollision(Entity* collidableEntity);
     void setUp(float xPos, float yPos, float length, float height, std::string name);
     sf::RectangleShape getShape();
     void move(sf::Vector2f newPos);
     void setPos(sf::Vector2f newPos);
};