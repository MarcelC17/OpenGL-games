#include "components/simple_scene.h"

class lives
{ 
    public: 
    int count;
    glm::mat3 pos[3];
    std::string name;

    lives(){
        count = 3;
        name = "Heart";
        pos[0] = {
            1,0,0,
            0,1,0,
            895, 658.5,1
        };

        pos[1] = {
            1,0,0,
            0,1,0,
            1038, 658.5,1
        };

        pos[2] = {
            1,0,0,
            0,1,0,
            1181, 658.5,1
        };
    }

    void add_life(){
        if (count < 3){
            count++;
        } 
    }

    void remove_life(){
        if (count > 0){
            count--;
        } 
    }  

}; 