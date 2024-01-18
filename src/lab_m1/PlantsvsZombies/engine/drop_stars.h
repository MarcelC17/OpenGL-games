#include "components/simple_scene.h"
#include "star_pos.h"

class drop_stars
{ 
    public: 
    std::vector<star_pos> stars;

    void add(star_pos e)
    {
        star_pos newStar;
        newStar.init(e.posSpawn, e.name, e.id);
        stars.push_back(newStar);
    }

    void remove(star_pos star)
    {
       for (auto i = stars.begin(); i < stars.end(); i++){
            if (i->id == star.id){
                stars.erase(i);
            }
       }
    }    

}; 