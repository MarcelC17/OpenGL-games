#include "components/simple_scene.h"
#include <string.h>

class projectile
{ 
    public: 
    glm::mat3 posSpawn;
    std::string name, color;
    int id,tx;
    float rotate, x, y;
    
    
    void init(glm::mat3 pos, std::string n, int ident){
        posSpawn = pos;
        id = ident;
        tx = 1.5;
        rotate = 0;
        color = n;

        x= posSpawn[2][0];
        y= posSpawn[2][1];


        if (color == "orange")
        {
            name = "Bullet_Orange";
        }
        if (color == "blue")
        {
            name = "Bullet_Blue";
        }
        if (color == "yellow")
        {
            name = "Bullet_Yellow";
        }
        if (color == "purple")
        {
            name = "Bullet_Purple";
        }
        
    }
}; 