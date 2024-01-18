#include "components/simple_scene.h"
#include "projectile.h"

class rounds
{ 
    public: 
    std::vector<projectile> loads;

    void add(projectile e)
    {
        projectile newProjectile;
        newProjectile.init(e.posSpawn,e.color,e.id);
        loads.push_back(newProjectile);
    }

    void remove(projectile projectile)
    {
       for (auto i = loads.begin(); i < loads.end(); i++){
            if (i->id == projectile.id){
                loads.erase(i);
            }
       }
    }    

}; 