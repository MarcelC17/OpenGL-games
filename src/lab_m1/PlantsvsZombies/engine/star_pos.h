#include "components/simple_scene.h"
#include <string.h>

class star_pos
{ 
    public: 
    glm::mat3 posSpawn;
    std::string name;
    float x, y;
    int id;   
    
    
    void init(glm::mat3 pos, std::string n, int ident){
        posSpawn = pos;
        x = posSpawn[2][0];
        y = posSpawn[2][1];

        id = ident;
        name = n;
    }
}; 