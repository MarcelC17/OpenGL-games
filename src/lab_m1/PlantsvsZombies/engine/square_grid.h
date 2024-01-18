#include "components/simple_scene.h"
#include <string.h>
#include "grid_pos.h"

class square_grid
{ 
    public: 
    std::vector<grid_pos> squares;
    
    void add(grid_pos pos){
        grid_pos new_pos;
        new_pos.init(pos.base);
        squares.push_back(new_pos);
    }
}; 