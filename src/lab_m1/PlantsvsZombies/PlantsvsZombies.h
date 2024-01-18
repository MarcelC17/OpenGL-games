#pragma once

#include "components/simple_scene.h"
#include "game_obj/Dreptunghi.h"
#include "game_obj/Patrat.h"
#include "game_obj/Cerc.h"
#include "game_obj/Inima.h"
#include "game_obj/Stea.h"
#include "game_obj/Tun.h"
#include "game_obj/Hexagon.h"
#include <stdlib.h>
#include "engine/wave.h"
#include "engine/square_grid.h"
#include "engine/weapon_squares.h"
#include "engine/rounds.h"
#include "engine/lives.h"
#include "engine/money.h"
#include "engine/drop_stars.h"



namespace m1
{
    class PlantsvsZombies : public gfxc::SimpleScene
    {
     public:
        PlantsvsZombies();
        ~PlantsvsZombies();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:

         //------------------------------------------------------------------------------//
         /* Screen resolution */
         glm::ivec2 resolution;

         /* Game objects meshes */
         Dreptunghi base;
         Patrat pot;
         Patrat grid;
         Inima heart;
         Stea star;
         Tun canon;
         Hexagon vilain;
         

         /* Stores position of stars and objects */
         glm::mat3 posMapElem, spawnStars;
         
         
         /* Random positions of enemies, stars on spawn */
         float enemy_spawn, star_spawn;

         /* Stores types of enemies and weapons */
         std::string enemy_type, weapon_type[4];
         
         //* Enemies on the map */
         wave enemy_wave;
         enemy bad_guy;

         /* Dynamic objects IDs */
         int id_enemy, id_misle, id_star;
         /* Shop items pozitions */
         square_grid sq_grid;
         grid_pos pos_sq;
         /* Canon pozitions */
         weapons_squares sq_weapons;
         weapon_pos pos_wp;
         
         /* Drag and drop helpers */
         //True if button is pressed
         bool pressed;
         //Current weapon
         weapon_pos chosen_weapon;
         //Coordinates selected weapon
         int drag_x,drag_y;
         
         /* Projectiles */
         projectile misle;
         rounds full_attack;
         float release_time;
         bool released;
         
         /* HP */
         lives hearts;
         
         /* money */
         money gold;

         /* stars posiztions */
         star_pos star_init;
         drop_stars star_grid;
   };
}
