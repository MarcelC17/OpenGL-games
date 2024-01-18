#include "Projectile.h"
#include <iostream>



class Bullets
{ 
    public: 
    std::vector<Projectile *> bullet_list;
    float reload;
    
    
    void add(Projectile* projectile){
        bullet_list.push_back(projectile);
    }

    void remove(Projectile* projectile){
        for (auto i = bullet_list.begin(); i < bullet_list.end(); i++){
            if (*i == projectile){
                bullet_list.erase(i);
            }
       }
    }
}; 