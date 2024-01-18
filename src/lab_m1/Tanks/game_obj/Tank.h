#include "lab_m1/Tanks/Tanks.h"
#include <iostream>
#include "Bullets.h"



class Tank
{ 
    public: 
    //atributes
    float scale = 0.2, speed = 20, top_angle = 0, action_duration = 0, change_action;
    //colors
    glm::vec3 initial_position = glm::vec3(1, 0, 0),  color_body = glm::vec3(1, 1, 1),
    color_base  = glm::vec3(1, 0.76, 0.77), color_steering = glm::vec3(1, 0.8, 0.95);

    unsigned int health;
    //position
    glm::mat4 body_matrix = glm::mat4(1);
    glm::mat4 top_matrix = glm::mat4(1);
    Bullets bullets;

    
    
    //init tank
    Tank(glm::mat4 InitMatrix){
        body_matrix = InitMatrix;
        body_matrix *= glm::scale(glm::mat4(1), glm::vec3(scale));
        body_matrix *=  glm::translate(glm::mat4(1), glm::vec3(0,0.5,0));

        top_matrix = InitMatrix;
        top_matrix *= glm::scale(glm::mat4(1), glm::vec3(scale));
        top_matrix *=  glm::translate(glm::mat4(1), glm::vec3(0,0.5,0));
        change_action = rand() % 2;
        health = 3;
    }

    //Rotate body and top
    void rotate_full(float angle){
        body_matrix *= glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
        top_matrix *= glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
    }

    void rotate_top(float angle){
        top_matrix *= glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
        top_angle += angle;
    }

    //Translate tank
    void translate(float deltaTime){
        glm::mat4 new_matrix =  body_matrix * glm::translate(glm::mat4(1), initial_position* speed *deltaTime);
        if (abs(new_matrix[3][0])< 47 && abs(new_matrix[3][2])< 47){
        body_matrix = new_matrix; 
        
        glm::mat4 translateTop = glm::rotate(glm::mat4(1), -top_angle, glm::vec3(0, 1, 0));
        translateTop *= glm::translate(glm::mat4(1), initial_position* speed *deltaTime);
        translateTop *= glm::rotate(glm::mat4(1), top_angle, glm::vec3(0, 1, 0));
        
        top_matrix *= translateTop;

        }
    }

    //Tank colission
    void colide(glm::vec3 distance){
        glm::mat4 new_matrix =  body_matrix * glm::translate(glm::mat4(1), distance);
        if (abs(new_matrix[3][0])< 47 && abs(new_matrix[3][2])< 47){
        body_matrix = new_matrix; 
        
        glm::mat4 translateTop = glm::rotate(glm::mat4(1), -top_angle, glm::vec3(0, 1, 0));
        translateTop *= glm::translate(glm::mat4(1), distance);
        translateTop *= glm::rotate(glm::mat4(1), top_angle, glm::vec3(0, 1, 0));
        
        top_matrix *= translateTop;
        }
    }
   
    //Reset tank animation timer
    void reset_action(){
        change_action = rand() % 2;
    }
}; 