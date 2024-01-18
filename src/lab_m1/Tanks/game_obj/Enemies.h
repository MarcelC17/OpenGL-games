#include "Tank.h"
#include "Buildings.h"
#include <iostream>
#include <cmath>




class Enemies
{ 
    public: 
    std::vector<Tank *> enemy_list;
    float enemy_spawn;
    
    void add(Tank* enemy){
        enemy_list.push_back(enemy);
    }

    void remove(Tank* enemy){
        for (auto i = enemy_list.begin(); i < enemy_list.end(); i++){
            if (*i == enemy){
                enemy_list.erase(i);
            }
       }
    }

    void animate(float deltaTime, Buildings braffles){
        for (auto i = enemy_list.begin(); i < enemy_list.end(); i++){
             
            (*i)->action_duration += deltaTime;
            
            if ((*i)->action_duration < (*i)->change_action){
                (*i)->rotate_full(deltaTime);
            }else if ((*i)->action_duration > (*i)->change_action && (*i)->action_duration < 4){
                
                for(auto j = braffles.buildings.begin(); j < braffles.buildings.end(); j++){

                float posx = abs((*j)->position_matrix[3][0] - (*i)->body_matrix[3][0]);
                float posy = abs((*j)->position_matrix[3][2] - (*i)->body_matrix[3][2]);
                float distance = sqrt(pow(posx, 2) + pow(posy, 2));
                    
        
                    if (distance < (*j)->scale ){
                        float P = (*j)->scale - distance; 
                        glm::mat4 MatDif = (*j)->position_matrix - (*i)->body_matrix;
                        glm::vec3 Dif = glm::vec3(MatDif[3][0], 0, MatDif[3][2]);
                        glm::vec3 DifNormal = glm::normalize(Dif); 
                        Dif = P * DifNormal;
                        
                        //colision enemy - enemy translate center    
                        (*i)->body_matrix[3][0] -= 0.5f * Dif[0];
                        (*i)->body_matrix[3][2] -= 0.5f * Dif[2];

                        (*i)->top_matrix[3][0] -= 0.5f * Dif[0];
                        (*i)->top_matrix[3][2] -= 0.5f * Dif[2];
                    }
                }
                (*i)->translate(deltaTime);
            }else{
                (*i)->action_duration = 0;
                (*i)->reset_action();
            }
       }
    }

}; 