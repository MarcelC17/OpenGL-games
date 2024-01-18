#include "lab_m1/PlantsvsZombies/PlantsvsZombies.h"

#include <vector>
#include <iostream>

#include "lab_m1/PlantsvsZombies/transform2D.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

PlantsvsZombies::PlantsvsZombies()
{
}

PlantsvsZombies::~PlantsvsZombies()
{
}

void PlantsvsZombies::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    
    /* Create object meshes */
    // purple rectangle
    Mesh *rectangle = base.create("Rectangle", glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);

    // green squares
    Mesh *square = pot.create("Square", glm::vec3(0, 1, 0), true);
    AddMeshToList(square);

    // weapon grid
    Mesh *weapon_grid = grid.create("Grid", glm::vec3(0.8, 0.8, 0.8), false);
    AddMeshToList(weapon_grid);

    // hearts
    Mesh *life = heart.create("Heart", glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    // weapon prices and stash 
    Mesh *money = star.create("Star", 7, glm::vec3(1, 0.07, 0.574));
    AddMeshToList(money);

    // dropping stars
    Mesh *drop_money = star.create("Star_drop", 10, glm::vec3(0.878, 1, 0.76));
    AddMeshToList(drop_money);

    // weapons
    Mesh *orange_weapon = canon.create("Orange_Canon", glm::vec3(1, 0.5, 0));
    weapon_type[0] = "Orange_Canon";
    AddMeshToList(orange_weapon);

    Mesh *blue_weapon = canon.create("Blue_Canon", glm::vec3(0, 0, 1));
    weapon_type[1] = "Blue_Canon";
    AddMeshToList(blue_weapon);

    Mesh *yellow_weapon = canon.create("Yellow_Canon", glm::vec3(1, 1, 0));
    weapon_type[2] = "Yellow_Canon";
    AddMeshToList(yellow_weapon);

    Mesh *purple_weapon = canon.create("Purple_Canon", glm::vec3(0.54, 0, 0.54));
    weapon_type[3] = "Purple_Canon";
    AddMeshToList(purple_weapon);

    /* Enemies */
    // outer
    Mesh *evil_outer = vilain.create("Enemy_outer_Purple", 30, glm::vec3(0.54, 0, 0.54));
    AddMeshToList(evil_outer);

    evil_outer = vilain.create("Enemy_outer_Yellow", 30, glm::vec3(1, 1, 0));
    AddMeshToList(evil_outer);

    evil_outer = vilain.create("Enemy_outer_Blue", 30, glm::vec3(0, 0, 1));
    AddMeshToList(evil_outer);

    evil_outer = vilain.create("Enemy_outer_Orange", 30, glm::vec3(1, 0.5, 0));
    AddMeshToList(evil_outer);
    
    //inner
    Mesh *evil_inner = vilain.create("Enemy_inner", 20, glm::vec3(0.4, 0.8, 0.66));
    AddMeshToList(evil_inner);

    //background
    base.height = resolution.y;
    base.width = resolution.x;
    Mesh *background = base.create("Background", glm::vec3(0.1, 0.1, 0.3), true);
    AddMeshToList(background);
    base.set_default();


    /* Bullets */
    Mesh *bullet = star.create("Bullet_Yellow", 12, glm::vec3(1, 1, 0));
    AddMeshToList(bullet);

    bullet = star.create("Bullet_Blue", 12, glm::vec3(0, 0, 1));
    AddMeshToList(bullet);

    bullet = star.create("Bullet_Orange", 12, glm::vec3(1, 0.5, 0));
    AddMeshToList(bullet);

    bullet = star.create("Bullet_Purple", 12, glm::vec3(0.54, 0, 0.54));
    AddMeshToList(bullet);

    enemy_spawn = 0;
    star_spawn = 0;
    id_enemy = 0;
    id_misle = 0;
    id_star = 0;
    posMapElem = glm::mat3(1);
    pressed = false;

    spawnStars = glm::mat3(1);

    gold.init(transform2D::Translate(2 * base.corner[0], 0));
}

void PlantsvsZombies::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void PlantsvsZombies::Update(float deltaTimeSeconds)
{   
    
    glm::mat3 pos_row1;
    glm::mat3 pos_row2;
    glm::mat3 pos_row3;

    /* Renders stars */
    for (auto i = star_grid.stars.begin(); i < star_grid.stars.end(); i++)
    {
        RenderMesh2D(meshes[i->name], shaders["VertexColor"], i->posSpawn);
    }

    /* Detects impact */
    // Iter. stars
    for (auto j = full_attack.loads.begin(); j < full_attack.loads.end(); j++)
    {
        //Iter. enemies
        for (auto i = enemy_wave.enemies.begin(); i < enemy_wave.enemies.end(); i++)
        {
            //Enemie death
            if (i->life == 0)
            {
                i->disapear = true;
            }
            // Checks for collision
            if (i->color == j->color && (((i->x - i->tx) - (j->x + j->tx)) < (vilain.radius + star.radius)) &&
                // Position on y and enemy life
                j->y < i->y && (j->y + 2 * pot.side / 3) > i->y && i->life > 0)
            {
                full_attack.remove(*j);
                i->life--;
            }
        }
    }

    /* Renders enemies */ 
    for (auto i = enemy_wave.enemies.begin(); i < enemy_wave.enemies.end(); i++)
    {
        // Enemy dissapearance Scale
        if (i->disapear == true)
        {
            i->scale_disapear -= deltaTimeSeconds;
            if (i->scale_disapear < 0)
            {
                enemy_wave.remove(*i);
            }
            // Inner hexa dissapearance
            RenderMesh2D(meshes["Enemy_inner"], shaders["VertexColor"], 
            i->posSpawn * transform2D::Translate(-i->tx, 0) * transform2D::Scale(i->scale_disapear, i->scale_disapear));
            
            // Outer hexa dissapearance
            RenderMesh2D(meshes[i->name], shaders["VertexColor"], 
            i->posSpawn * transform2D::Translate(-i->tx, 0) * transform2D::Scale(i->scale_disapear, i->scale_disapear));
        }
        else
        // Enemy transition 
        {
            i->tx += 100 * deltaTimeSeconds;
            //If base (purple rectangle) reached
            if (i->x - i->tx < base.corner[0] + base.width)
            {
                hearts.remove_life();
                i->disapear = true;
            }

            RenderMesh2D(meshes["Enemy_inner"], shaders["VertexColor"], i->posSpawn * transform2D::Translate(-i->tx, 0));

            RenderMesh2D(meshes[i->name], shaders["VertexColor"], i->posSpawn * transform2D::Translate(-i->tx, 0));
        }
    }

    /* Renders hearts */
    for (int i = 0; i < hearts.count; i++)
    {
        RenderMesh2D(meshes[hearts.name], shaders["VertexColor"], hearts.pos[i]);
    }

    /* Renders money */
    for (int i = 0; i < gold.count; i++)
    {
        RenderMesh2D(meshes[gold.name], shaders["VertexColor"], gold.pos[i]);
    }

    /* Renders weapon while drag */
    if (pressed)
    {
        RenderMesh2D(meshes[chosen_weapon.color], shaders["VertexColor"], transform2D::Translate(drag_x, drag_y));
    }

    /* Renders projectiles */
    for (auto i = full_attack.loads.begin(); i < full_attack.loads.end(); i++)
    {
        i->tx += 200 * deltaTimeSeconds;
        i->rotate += 3 * deltaTimeSeconds;
        if (i->rotate > 6.28)
        {
            i->rotate = 0;
        }

        //Rotates bullets
        RenderMesh2D(meshes[i->name], shaders["VertexColor"], 
        i->posSpawn * transform2D::Translate(canon.width * 1.5 + i->tx, pot.side / 2.1) 
        * transform2D::Rotate(i->rotate) * transform2D::Translate(0, -15));
    }

    /* Render weapons */
    for (auto i = sq_grid.squares.begin(); i < sq_grid.squares.end(); i++)
    {
        
        if (i->busy == true && i->disapear == false)
        {
            i->release_time += deltaTimeSeconds;
            RenderMesh2D(meshes[i->weapon], shaders["VertexColor"], i->base * transform2D::Translate(2 * base.corner[0], pot.side / 2));

            for (auto j = enemy_wave.enemies.begin(); j < enemy_wave.enemies.end(); j++)
            {
                // Checks for colision
                if (i->y < j->y && (i->y + pot.side) > j->y && (j->x - j->tx) - i->x < pot.side && (j->x - j->tx) - i->x  > 0)
                {
                    cout<< "abs:          "<<abs((j->x - j->tx) - i->x)<<"/n;";
                    cout<< "side:          "<<pot.side<<"/n;";

                    i->disapear = true;
                }

                if (i->y < j->y && (i->y + pot.side) > j->y && (i->color == j->color) &&
                    (i->release_time > 2) && ((j->x - j->tx) < 1100))
                {
                    misle.init(i->base, i->color, id_misle);
                    full_attack.add(misle);
                    id_misle++;
                    i->release_time = 0;
                }
            }
            
        }
        else if (i->busy == true && i->disapear == true)
        {
            // Weapon dissapearance scale
            if (i->scale_disapear < 0)
            {
                i->free();
            }
            else
            {
                i->scale_disapear -= deltaTimeSeconds;
                RenderMesh2D(meshes[i->weapon], shaders["VertexColor"], i->base * transform2D::Translate(2 * base.corner[0], pot.side / 2) * transform2D::Scale(i->scale_disapear, i->scale_disapear));
            }
        }
    }

    //Renders green squares and base
    RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], glm::mat3(1));
    for (int i = 0; i < 3; i++)
    {
        posMapElem = transform2D::Translate(base.corner[0], base.corner[1]);
        posMapElem *= transform2D::Translate(0, i * (pot.side + base.corner[1]));

        for (int j = 0; j < 3; j++)
        {

            if (j == 0)
                posMapElem *= transform2D::Translate(base.width, 0);
            else
            {
                posMapElem *= transform2D::Translate(pot.side, 0);
            }
            posMapElem *= transform2D::Translate(base.corner[0], 0);

            if (sq_grid.squares.size() < 9)
            {
                pos_sq.init(posMapElem);
                sq_grid.add(pos_sq);
            }

            RenderMesh2D(meshes["Square"], shaders["VertexColor"], posMapElem);
            // Stores rows positions
            switch (i)
            {
            case 0:
                pos_row1 = posMapElem * transform2D::Translate(7 * pot.side, pot.side / 2);
                break;
            case 1:
                pos_row2 = posMapElem * transform2D::Translate(7 * pot.side, pot.side / 2);
                break;  
            case 2:
                pos_row3 = posMapElem * transform2D::Translate(7 * pot.side, pot.side / 2);
                break;
            }

            pos_row3 = posMapElem * transform2D::Translate(7 * pot.side, pot.side / 2);
        }
    }

   // Renderes canons and grid

    posMapElem = transform2D::Translate(base.corner[0], resolution.y - pot.side - base.corner[0]);

    if (sq_weapons.squares.size() < 4)
    {
        pos_wp.init(posMapElem, weapon_type[0]);
        sq_weapons.add(pos_wp);
    }

    RenderMesh2D(meshes["Grid"], shaders["VertexColor"], posMapElem);

    glm::mat3 posCanon = posMapElem;
    for (int i = 0; i < 4; i++)
    {
        posCanon = posMapElem;
        posCanon *= transform2D::Translate(pot.side / 4, pot.side / 2);
        posMapElem *= transform2D::Translate(2 * base.corner[0] + pot.side, 0);
        RenderMesh2D(meshes[weapon_type[i]], shaders["VertexColor"], posCanon);

        if (sq_weapons.squares.size() < 4 && i < 3)
        {
            pos_wp.init(posMapElem, weapon_type[i + 1]);
            sq_weapons.add(pos_wp);
        }
        if (i < 3)
            RenderMesh2D(meshes["Grid"], shaders["VertexColor"], posMapElem);
    }

    // Renders cannon prices
    glm::mat3 posStar = transform2D::Translate(2 * base.corner[0], resolution.y - 1.3 * pot.side);
    RenderMesh2D(meshes["Star"], shaders["VertexColor"], posStar);

    for (int i = 0; i < 3; i++)
    {
        posStar *= transform2D::Translate(2 * base.corner[0] + pot.side, 0);
        glm::mat3 WeaponCostPos = posStar;
        for (int j = 0; j <= i + 1; j++)
        {
            if (j == 1)
                j++;
            RenderMesh2D(meshes["Star"], shaders["VertexColor"], WeaponCostPos);
            WeaponCostPos *= transform2D::Translate(2 * base.corner[0], 0);
        }
    }

    /* Renders background */
    RenderMesh2D(meshes["Background"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(-base.corner[0], -base.corner[1]));

    // Spawns enemies
    enemy_spawn += deltaTimeSeconds;

    if (enemy_spawn > 4)
    {

        switch (rand() % 4)
        {
        case 0:
            enemy_type = "Enemy_outer_Orange";
            break;
        case 1:
            enemy_type = "Enemy_outer_Yellow";
            break;
        case 2:
            enemy_type = "Enemy_outer_Blue";
            break;
        case 3:
            enemy_type = "Enemy_outer_Purple";
            break;
        }

        switch (rand() % 3)
        {
        case 0:
            bad_guy.init(pos_row1, enemy_type, id_enemy);
            enemy_wave.add(bad_guy);
            id_enemy++;
            break;

        case 1:
            bad_guy.init(pos_row2, enemy_type, id_enemy);
            enemy_wave.add(bad_guy);
            id_enemy++;
            break;

        case 2:
            bad_guy.init(pos_row3, enemy_type, id_enemy);
            enemy_wave.add(bad_guy);
            id_enemy++;
            break;
        }
        enemy_spawn = 0;
    }

    // Spawns stars
    star_spawn += deltaTimeSeconds;
    if (star_spawn > 10)
    {
        spawnStars[2][0] = rand() % resolution.x;
        spawnStars[2][1] = rand() % resolution.y;
        star_init.init(spawnStars, "Star_drop", id_star);
        id_star++;
        star_grid.add(star_init);

        spawnStars[2][0] = rand() % resolution.x;
        spawnStars[2][1] = rand() % resolution.y;
        star_init.init(spawnStars, "Star_drop", id_star);
        id_star++;
        star_grid.add(star_init);

        spawnStars[2][0] = rand() % resolution.x;
        spawnStars[2][1] = rand() % resolution.y;
        star_init.init(spawnStars, "Star_drop", id_star);
        id_star++;
        star_grid.add(star_init);

        star_spawn = 0;
    }
}

void PlantsvsZombies::FrameEnd()
{
}

void PlantsvsZombies::OnInputUpdate(float deltaTime, int mods)
{
}

void PlantsvsZombies::OnKeyPress(int key, int mods)
{
}

void PlantsvsZombies::OnKeyRelease(int key, int mods)
{
}

void PlantsvsZombies::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    /* Stores x and y positions for drag and drop */
    if (pressed)
    {
        drag_x = mouseX;
        drag_y = resolution.y - mouseY;
    }
}

void PlantsvsZombies::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    mouseY = resolution.y - mouseY;
    /* Selects weapon */
    for (auto i = sq_weapons.squares.begin(); i < sq_weapons.squares.end(); i++)
    {
        if (mouseX < (i->x + pot.side) && (mouseX > i->x) && (mouseY > i->y) && (mouseY < (i->y + pot.side)) && button == 1)
        {
            pressed = true;
            chosen_weapon = *i;
            drag_x = mouseX;
            drag_y = mouseY;
        }
    }

    /* Collects star */
    for (auto i = star_grid.stars.begin(); i < star_grid.stars.end(); i++)
    {
        if (mouseX > i->x - base.corner[0] && mouseX < i->x + base.corner[0] && mouseY > i->y - base.corner[0] / 4 && mouseY < i->y + 1.8 * base.corner[0] && gold.count < 9 && button == 1)
        {
            star_grid.remove(*i);
            gold.add_star();
        }
    }
}

void PlantsvsZombies::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

    mouseY = resolution.y - mouseY;
    for (auto i = sq_grid.squares.begin(); i < sq_grid.squares.end(); i++)
    {
        /* Adds weapon to green square */
        if (pressed)
        {
            if (mouseX < (i->x + pot.side) && (mouseX > i->x) && (mouseY > i->y) 
            && (mouseY < (i->y + pot.side)) && !i->busy && button == 1 && gold.count - chosen_weapon.price >= 0)
            {
                i->new_weapon(chosen_weapon.color);
                gold.remove_star(chosen_weapon.price);
            }
        }
        /* Removes weapon from square */
        else if (mouseX < (i->x + pot.side) && (mouseX > i->x) && (mouseY > i->y) && (mouseY < (i->y + pot.side)) && i->busy && button == 2)
        {
            i->release();
        }
    }
    pressed = false;
}

void PlantsvsZombies::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void PlantsvsZombies::OnWindowResize(int width, int height)
{
}
