    #include "Entity.h"
     void Entity::setUp(float xPos, float yPos, float length, float height, std::string name)
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



    sf::RectangleShape Entity::getShape()
    {
        return this->drawable;
    }


    void Entity::move(sf::Vector2f newPos)
    {
        this->xPos += newPos.x;
        this->yPos += newPos.y;
        

    }

    void Entity::setPos(sf::Vector2f newPos)
    {
        this->xPos = newPos.x;
        this->yPos = newPos.y;
        
    }

     bool Entity::checkCollision(Entity* collidableEntity) 
    {
        return
                xPos + length >= collidableEntity->xPos &&
                xPos <= collidableEntity->xPos + collidableEntity->length &&
                yPos + height >= collidableEntity->yPos &&
                yPos <= collidableEntity->yPos + collidableEntity->height;
                

    }