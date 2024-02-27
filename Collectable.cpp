#include "Entity.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

class Collectable : public Entity
{
private:
    /* data */
public:
    Player* ptr_player;


    Collectable(Player* ptr_player)
    {
        this->ptr_player = ptr_player;
        this->toggle = true;
        this->drawable.setFillColor(sf::Color::Yellow);
    }

    
 
    bool checkCollision(Entity* collidableEntity)
    override {
        if(     xPos + length >= collidableEntity->xPos &&
                xPos <= collidableEntity->xPos + collidableEntity->length &&
                yPos + height >= collidableEntity->yPos &&
                yPos <= collidableEntity->yPos + collidableEntity->height)
        {
           
            if (collidableEntity->name == "player" && this->toggle)
            {
                 std::cout << "visibility disabled";
                this->toggle = false;
                //ptr_player->score += 1;
                ptr_player->score += 1;
                
            }
                          
        }
        return false;
    }
};