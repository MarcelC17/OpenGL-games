#include <iostream>
#include "lab_m1/Tanks/Tanks.h"





class House
{ 
    public: 
    float scale = 1;
    glm::vec3 color = glm::vec3(0, 0, 0), initial_scale = glm::vec3(1, 2, 1);
    glm::mat4 position_matrix = glm::mat4(1);
    
    
    

    House(glm::mat4 InitMatrix, glm::vec3 new_color, float to_scale){
        position_matrix = InitMatrix;
        scale = to_scale;
        color = new_color;
        
        position_matrix = glm::translate(position_matrix, glm::vec3(0,1,0));
        position_matrix = glm::translate(position_matrix, glm::vec3(0,scale/2,0));
        position_matrix = glm::scale(position_matrix, initial_scale);
        position_matrix = glm::scale(position_matrix, glm::vec3(scale, scale, scale));
    }


}; 