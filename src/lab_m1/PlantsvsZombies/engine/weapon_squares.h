#include "components/simple_scene.h"
#include "weapon_pos.h"

class weapons_squares
{ 
    public: 
    std::vector<weapon_pos> squares;
    
    void add(weapon_pos pos){
        weapon_pos new_pos;
        new_pos.init(pos.base, pos.color);
        squares.push_back(new_pos);
    }
}; 