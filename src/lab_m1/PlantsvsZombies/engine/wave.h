#include "components/simple_scene.h"
#include "enemy.h"

class wave
{ 
    public: 
    std::vector<enemy> enemies;

    void add(enemy e)
    {
        enemy newEnemy;
        newEnemy.init(e.posSpawn,e.name,e.id);
        enemies.push_back(newEnemy);
    }

    void remove(enemy enemy)
    {
       for (auto i = enemies.begin(); i < enemies.end(); i++){
            if (i->id == enemy.id){
                enemies.erase(i);
            }
       }
    }    

}; 