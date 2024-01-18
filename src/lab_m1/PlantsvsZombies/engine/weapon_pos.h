#include "components/simple_scene.h"
#include <string.h>

class weapon_pos
{ 
    public: 
    
    int price;
    glm::mat3 base;
    float x, y;
    std::string color;

    
    void init(glm::mat3 b, std::string col){
        base = b;
        x = base[2][0];
        y = base[2][1];
        color = col;

        if (col == "Orange_Canon")
        {
            price = 1;
        } 
        if (col == "Blue_Canon"){
            price = 2;
        }
        if (col == "Yellow_Canon"){
            price = 2;
        }
        if (col == "Purple_Canon"){
            price = 3;
        }
        

    }
}; 