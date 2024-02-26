#include "Entity.h"

class Collectable : public Entity
{
private:
    /* data */
public:
    


    bool checkCollision(Entity* collidableEntity)
    override {
        if(     xPos + length >= collidableEntity->xPos &&
                xPos <= collidableEntity->xPos + collidableEntity->length &&
                yPos + height >= collidableEntity->yPos &&
                yPos <= collidableEntity->yPos + collidableEntity->height)
        {
           
            if (collidableEntity->name == "player")
            {
                 std::cout << "visibility disabled";
                this->toggle = false;
            }
                          
        }
        return false;
    }
};