#include "lab_m1/Tanks/Tanks.h"
#include <iostream>



class Projectile
{ 
    public: 
    float scale = 1, speed = 100, lifetime = 0;
    
    glm::mat4 renderMatrix = glm::mat4(1);
    

    
    

    Projectile(glm::mat4 InitMatrix){
        renderMatrix = InitMatrix;
        renderMatrix *= glm::translate(glm::mat4(1), glm::vec3(10.5, 3.5, 0));
        renderMatrix *= glm::scale(glm::mat4(1), glm::vec3(scale));
    }

    void translate(float deltaTimeSeconds){
        lifetime += deltaTimeSeconds;
        renderMatrix *= glm::translate(glm::mat4(1),  glm::vec3(1,0,0) * speed * deltaTimeSeconds);
    } 
}; 