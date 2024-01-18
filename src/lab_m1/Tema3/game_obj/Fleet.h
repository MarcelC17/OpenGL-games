#include "Boat.h"
#include <iostream>



class Fleet
{ 
    public: 
    std::vector<Boat *> boats;
    
    
    void add(Boat* boat){
        boats.push_back(boat);
    }

    void remove(Boat* boat){
        for (auto i = boats.begin(); i < boats.end(); i++){
            if (*i == boat){
                boats.erase(i);
            }
       }
    }
}; 