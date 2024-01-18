#include "components/simple_scene.h"
#include <string.h>

class grid_pos
{ 
    public: 
    bool busy, disapear;
    glm::mat3 base;
    std::string weapon, color;
    float x, y, scale_disapear, release_time;
    
    void init(glm::mat3 b){
        busy = false;

        base = b;
        x = base[2][0];
        y = base[2][1];

        disapear = false;
        scale_disapear = 1;
        release_time = 0;

    }

    void free(){
        busy = false;
        disapear = false;
        scale_disapear = 1;
        color = "none";
    }

    void release(){
        disapear = true;
    }

    void new_weapon(std::string wp){
        busy = true;
        weapon = wp;
        if (wp == "Orange_Canon")
        {
            color = "orange";
        }
        if (wp == "Blue_Canon")
        {
            color = "blue";
        }
        if (wp == "Yellow_Canon")
        {
            color = "yellow";
        }
        if (wp == "Purple_Canon")
        {
            color = "purple";
        }
    }

}; 