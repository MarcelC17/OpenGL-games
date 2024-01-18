#include "House.h"
#include <iostream>



class Buildings
{ 
    public: 
    std::vector<House *> buildings;
    float reload;
    
    
    void add(House* house){
        buildings.push_back(house);
    }

    void remove(House* house){
        for (auto i = buildings.begin(); i < buildings.end(); i++){
            if (*i == house){
                buildings.erase(i);
            }
       }
    }
}; 