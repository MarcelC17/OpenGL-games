#include "components/simple_scene.h"

class money
{ 
    public: 
    int count;
    glm::mat3 pos[9];
    std::string name;

    money(){

    }

    void init(glm::mat3 trans){
        count = 9;
        name = "Star";
        pos[0] = {
            1,0,0,
            0,1,0,
            895, 558.5, 1
        };

        for (int i = 1; i < 9; i++)
        {
            pos[i] = pos[i-1] * trans;
        }
    }

    void add_star(){
        if (count < 9){
            count++;
        } 
    }

    void remove_star(int cost){
        if (count - cost >= 0){
            count -= cost;
        } 
    }  

}; 