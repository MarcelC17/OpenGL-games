#include "components/simple_scene.h"
#include <string.h>

class enemy
{ 
    public: 
    glm::mat3 posSpawn;
    std::string name, color;
    int id, tx, life;
    float x, y, scale_disapear;
    bool disapear;    
    
    
    void init(glm::mat3 pos, std::string n, int ident){
        posSpawn = pos;
        name = n;
        id = ident;
        tx = 1;
        life = 3;
        disapear = false;
        scale_disapear = 1;
        

        x= posSpawn[2][0];
        y= posSpawn[2][1];
        
       if (name == "Enemy_outer_Orange")
        {
            color = "orange";
        }
        if (name == "Enemy_outer_Blue")
        {
            color = "blue";
        }
        if (name == "Enemy_outer_Yellow")
        {
           color = "yellow";
        }
        if (name == "Enemy_outer_Purple")
        {
            color = "purple";
        }
    }
}; 