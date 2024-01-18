#include "lab_m1/Tanks/Tanks.h"



class Boat
{ 
    public: 
    //atributes
    float scale = 0.2, speed = 20, radius; 
    glm::mat4 move_circle;
    //colors
    glm::vec3 initial_position = glm::vec3(1, 0, 0);

    //position
    glm::mat4 body_matrix = glm::mat4(1);
    Bullets bullets;

    
    
    //init boat
    Boat(glm::mat4 InitMatrix, float new_radius){
        body_matrix = InitMatrix;
        // body_matrix *= glm::rotate(glm::mat4(1), 2, glm::vec3(0, 1, 0));
        body_matrix *= glm::scale(glm::mat4(1), glm::vec3(scale));
        move_circle = body_matrix;
        radius = new_radius;
        
    }


    // Translate boat
    void Move(float deltaTime){
        body_matrix = move_circle;
        body_matrix *=  glm::rotate(glm::mat4(1), deltaTime, glm::vec3(0, 1, 0));
        move_circle = body_matrix;
        body_matrix *=  glm::translate(glm::mat4(1), glm::vec3(radius/scale,0,0));
        body_matrix *=  glm::rotate(glm::mat4(1), deltaTime, glm::vec3(0, 1, 0));

    }
}; 