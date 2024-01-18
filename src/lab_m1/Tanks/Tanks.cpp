#include "lab_m1/Tanks/Tanks.h"


using namespace std;
using namespace m1;


Tanks::Tanks()
{

}


Tanks::~Tanks()
{
}


void Tanks::Init()
{   
    

    //Initializes tank matrix, game times
    tank = new Tank(glm::mat4(1));
    enemies.enemy_spawn = 0; 
    game_time = 0;

    //Loads tank body meshes
    Mesh* mesh; 
    {
        mesh = new Mesh("body");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "body.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("body_aux");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "body_aux.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("leftst");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "leftst.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("leftwh");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "leftwh.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("rightst");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "rightst.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("rightwh");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "rightwh.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("stearing");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "stearing.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    //Loads tank gun
    {
        mesh = new Mesh("top_base");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "top_base.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("top_cannon");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "top_cannon.obj");
        meshes[mesh->GetMeshID()] = mesh;
        
        mesh = new Mesh("top_connection");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/tank"), "top_connection.obj");
        meshes[mesh->GetMeshID()] = mesh;

    }

    //Loads projectile, plane and buildings
    {
        mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("plane50");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("building");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    
    //Set light parameters
    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }

    //Creates a shader program
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tanks", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tanks", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //Initializes buildings
    for (int i = 0; i < 30; i++){
        float scale = rand() % 2 + 4;

         int x, y;

        do{
        x = (rand() % 90 - scale) - 45 + scale / 2;
        y = (rand() % 90 - scale) - 45 + scale / 2;
        } while (abs(x) < 5 || abs(y) < 5);

        glm::mat4 spawnPos = glm::mat4(1);

        spawnPos[3][0] = x;
        spawnPos[3][2] = y;

        float r = ((float)(rand() % 40 + 50)) / 100;
        float g = ((float)(rand() % 40 + 50)) / 100;
        float b = ((float)(rand() % 40 + 50)) / 100;

        braffles.add(new House(spawnPos, glm::vec3(r,g,b),scale));
    }

    //Sets camera
    renderCameraTarget = false;
    camera = new cam::Camera();
    camera->Set(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->RotateThirdPerson_OY(-1.57);

    //Set score
    score = 0;
    ended = false;
    

    //Remove hardcodings of parameters
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Tanks::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tanks::RenderScene() {

}


void Tanks::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color, unsigned int health)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_position, 1, glm::value_ptr(lightPosition));

    // Tank hp to shader
    int life_position = glGetUniformLocation(shader->program, "life");
    glUniform1i(life_position, health);

    int material = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	int object_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(object_color, 1, glm::value_ptr(color));

    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tanks::Update(float deltaTimeSeconds)
{
    //Game duration
    game_time += deltaTimeSeconds;

        enemies.enemy_spawn += deltaTimeSeconds;
        
        //Add enemies
        if (enemies.enemy_spawn > 0 && enemies.enemy_list.size() < 20){
            glm::mat4 spawnPos = glm::mat4(1);

           
            float distance = 0;
            int x,y;

            while(distance < 10){
                x = (rand() % 90) - 45;
                y = (rand() % 90) - 45;

                float posx = abs(x - tank->body_matrix[3][0]);
                float posy = abs(y - tank->body_matrix[3][2]);
                distance = sqrt(pow(posx, 2) + pow(posy, 2));
            }

            spawnPos[3][0] = x;
            spawnPos[3][2] = y;

            enemies.add(new Tank(spawnPos));
            enemies.enemy_spawn = 0;
        }
        
        //Animate enemies
        if (game_time<90)
        enemies.animate(deltaTimeSeconds, braffles);
        
        //Render enemies
        for (auto i = enemies.enemy_list.begin(); i < enemies.enemy_list.end(); i++){
            {
                RenderSimpleMesh(meshes["top_base"], shaders["LabShader"], (*i)->top_matrix, (*i)->color_base, (*i)->health);
                RenderSimpleMesh(meshes["top_cannon"], shaders["LabShader"], (*i)->top_matrix, (*i)->color_base,(*i)->health);
                RenderSimpleMesh(meshes["top_connection"], shaders["LabShader"], (*i)->top_matrix, (*i)->color_base,(*i)->health);
            }

            {
            RenderSimpleMesh(meshes["body"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_base,(*i)->health);
            RenderSimpleMesh(meshes["body_aux"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_base, (*i)->health);
            RenderSimpleMesh(meshes["leftst"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_steering, 3);
            RenderSimpleMesh(meshes["leftwh"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_body, 3);
            RenderSimpleMesh(meshes["rightst"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_steering, 3);
            RenderSimpleMesh(meshes["rightwh"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_body, 3);
            RenderSimpleMesh(meshes["stearing"], shaders["LabShader"], (*i)->body_matrix, (*i)->color_base, (*i)->health);
            }


            //Computes distance to tank
            float posx = abs((*i)->body_matrix[3][0] - tank->body_matrix[3][0]);
            float posy = abs((*i)->body_matrix[3][2] - tank->body_matrix[3][2]);
            float distance = sqrt(pow(posx, 2) + pow(posy, 2)); 
            float R = 2;

            //Colision to tank
            if (distance < 2*R){
                float P = 2*R - distance; 
                glm::mat4 MatDif = (*i)->body_matrix - tank->body_matrix;
                glm::vec3 Dif = glm::vec3(MatDif[3][0], 0, MatDif[3][2]);
                glm::vec3 DifNormal = glm::normalize(Dif); 
                Dif = P * DifNormal;

                (*i)->body_matrix[3][0] += 0.5f * Dif[0];
                (*i)->body_matrix[3][2] += 0.5f * Dif[2];

                (*i)->top_matrix[3][0] += 0.5f * Dif[0];
                (*i)->top_matrix[3][2] += 0.5f * Dif[2];

                tank->body_matrix[3][0] -= 0.5f * Dif[0];
                tank->body_matrix[3][2] -= 0.5f * Dif[2];

                tank->top_matrix[3][0] -= 0.5f * Dif[0];
                tank->top_matrix[3][2] -= 0.5f * Dif[2];
            }

            for (auto j = enemies.enemy_list.begin(); j < enemies.enemy_list.end(); j++){
                if (i != j){
                    //Calculate distance enemy-enemy
                    float posx = abs((*i)->body_matrix[3][0] - (*j)->body_matrix[3][0]);
                    float posy = abs((*i)->body_matrix[3][2] - (*j)->body_matrix[3][2]);
                    float distance = sqrt(pow(posx, 2) + pow(posy, 2));
                    float R = 2;

                    //Colision enemy-enemy
                    if (distance < 2*R){
                        float P = 2*R - distance; 
                        glm::mat4 MatDif = (*i)->body_matrix - (*j)->body_matrix;
                        glm::vec3 Dif = glm::vec3(MatDif[3][0], 0, MatDif[3][2]);
                        glm::vec3 DifNormal = glm::normalize(Dif); 
                        Dif = P * DifNormal;

                        (*i)->body_matrix[3][0] += 0.5f * Dif[0];
                        (*i)->body_matrix[3][2] += 0.5f * Dif[2];

                        (*i)->top_matrix[3][0] += 0.5f * Dif[0];
                        (*i)->top_matrix[3][2] += 0.5f * Dif[2];

                        (*j)->body_matrix[3][0] -= 0.5f * Dif[0];
                        (*j)->body_matrix[3][2] -= 0.5f * Dif[2];

                        (*j)->top_matrix[3][0] -= 0.5f * Dif[0];
                        (*j)->top_matrix[3][2] -= 0.5f * Dif[2];
                    }
                }
            }
        }

        //Update bullet reload time
        tank->bullets.reload += deltaTimeSeconds;
        
        //Render bullets
        for (auto i = tank->bullets.bullet_list.begin(); i < tank->bullets.bullet_list.end(); i++){
            RenderSimpleMesh(meshes["projectile"], shaders["LabShader"], (*i)->renderMatrix, glm::vec3(0.2,0.2,0.2), 3);
            (*i)->translate(deltaTimeSeconds);

            //Remove bullet
            //Colision to tank
            if ((*i)->lifetime > 10) tank->bullets.remove((*i));
            for (auto j = enemies.enemy_list.begin(); j < enemies.enemy_list.end(); j++){
                if (abs((*i)->renderMatrix[3][0] - (*j)->body_matrix[3][0]) < 1.63 &&
                    abs((*i)->renderMatrix[3][2] - (*j)->body_matrix[3][2]) < 1.13){
                    if ((*j)->health == 1) {
                        enemies.remove(*j);
                        score++;
                    }
                    else{
                        (*j)->health--;
                    } 
                    tank->bullets.remove((*i));
                }
            }

            //Colision to building
            for(auto j = braffles.buildings.begin(); j < braffles.buildings.end(); j++){

                float posx = abs((*j)->position_matrix[3][0] - (*i)->renderMatrix[3][0]);
                float posy = abs((*j)->position_matrix[3][2] - (*i)->renderMatrix[3][2]);
                float distance = sqrt(pow(posx, 2) + pow(posy, 2));
                    
        
                if (distance < (*j)->scale - 2){
                    tank->bullets.remove((*i));
                }
            }

        }

        //Render tank
        //Top
        {
            RenderSimpleMesh(meshes["top_base"], shaders["LabShader"], tank->top_matrix, tank->color_base, tank->health);
            RenderSimpleMesh(meshes["top_cannon"], shaders["LabShader"], tank->top_matrix, tank->color_base,tank->health);
            RenderSimpleMesh(meshes["top_connection"], shaders["LabShader"], tank->top_matrix, tank->color_base,tank->health);
        }
        //Body
        {
        RenderSimpleMesh(meshes["body"], shaders["LabShader"], tank->body_matrix, tank->color_base,tank->health);
        RenderSimpleMesh(meshes["body_aux"], shaders["LabShader"], tank->body_matrix, tank->color_base, tank->health);
        RenderSimpleMesh(meshes["leftst"], shaders["LabShader"], tank->body_matrix, tank->color_steering, 3);
        RenderSimpleMesh(meshes["leftwh"], shaders["LabShader"], tank->body_matrix, tank->color_body, 3);
        RenderSimpleMesh(meshes["rightst"], shaders["LabShader"], tank->body_matrix, tank->color_steering, 3);
        RenderSimpleMesh(meshes["rightwh"], shaders["LabShader"], tank->body_matrix, tank->color_body, 3);
        RenderSimpleMesh(meshes["stearing"], shaders["LabShader"], tank->body_matrix, tank->color_base, tank->health);
        }


        //Render plane
        RenderSimpleMesh(meshes["plane50"], shaders["LabShader"], glm::scale(glm::mat4(1), glm::vec3(2,1,2)),  glm::vec3(0.1, 0.76, 0.77), 3);
        
        //Render buildings
        for (auto i = braffles.buildings.begin(); i < braffles.buildings.end(); i++){
            RenderSimpleMesh(meshes["building"], shaders["LabShader"], (*i)->position_matrix, (*i)->color, 3);
        }
        
        if (game_time > 90 && !ended){
        cout << "Score:  " << score << endl;
        ended = true;
        }
}

void Tanks::FrameEnd()
{
}


void Tanks::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)){
        //Move forward
        if (window->KeyHold(GLFW_KEY_W)){
            //Building collision
            for(auto i = braffles.buildings.begin(); i < braffles.buildings.end(); i++){

                float posx = abs((*i)->position_matrix[3][0] - tank->body_matrix[3][0]);
                float posy = abs((*i)->position_matrix[3][2] - tank->body_matrix[3][2]);
                float distance = sqrt(pow(posx, 2) + pow(posy, 2));
                    
        
                    if (distance < (*i)->scale ){
                        float P = (*i)->scale - distance; 
                        glm::mat4 MatDif = (*i)->position_matrix - tank->body_matrix;
                        glm::vec3 Dif = glm::vec3(MatDif[3][0], 0, MatDif[3][2]);
                        glm::vec3 DifNormal = glm::normalize(Dif); 
                        Dif = P * DifNormal;
                        
                        tank->body_matrix[3][0] -= 0.5f * Dif[0];
                        tank->body_matrix[3][2] -= 0.5f * Dif[2];

                        tank->top_matrix[3][0] -= 0.5f * Dif[0];
                        tank->top_matrix[3][2] -= 0.5f * Dif[2];
                    }
                }
            if (game_time < 90){
            tank->translate(deltaTime);
            //Move camera
            camera->TranslateForward(deltaTime * tank->speed/5);
            }
        } else if (window->KeyHold(GLFW_KEY_S)){
            //Move back
            //Building collision
            for(auto i = braffles.buildings.begin(); i < braffles.buildings.end(); i++){

                float posx = abs((*i)->position_matrix[3][0] - tank->body_matrix[3][0]);
                float posy = abs((*i)->position_matrix[3][2] - tank->body_matrix[3][2]);
                float distance = sqrt(pow(posx, 2) + pow(posy, 2));
                    
        
                    if (distance < (*i)->scale ){
                        float P = (*i)->scale - distance; 
                        glm::mat4 MatDif = (*i)->position_matrix - tank->body_matrix;
                        glm::vec3 Dif = glm::vec3(MatDif[3][0], 0, MatDif[3][2]);
                        glm::vec3 DifNormal = glm::normalize(Dif); 
                        Dif = P * DifNormal;
                        
                        //colision enemy - enemy translate center    
                        tank->body_matrix[3][0] -= 0.5f * Dif[0];
                        tank->body_matrix[3][2] -= 0.5f * Dif[2];

                        tank->top_matrix[3][0] -= 0.5f * Dif[0];
                        tank->top_matrix[3][2] -= 0.5f * Dif[2];
                    }
                }
            if (game_time < 90){ 
            tank->translate(-deltaTime);
            //Move camera
            camera->TranslateForward(-deltaTime * tank->speed/5);
            }   
        }else if (window->KeyHold(GLFW_KEY_A)){
            //Rotate camera and tank
            camera->RotateThirdPerson_OY(0.0168);
            tank->rotate_full(deltaTime);
        } else if (window->KeyHold(GLFW_KEY_D)){
            //Rotate camera and tank
            camera->RotateThirdPerson_OY(-0.0168);
           tank->rotate_full(-deltaTime);
        }
    }
}


void Tanks::OnKeyPress(int key, int mods)
{
    
}


void Tanks::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tanks::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    //Rotate tank top
    tank->rotate_top(-3.14 * deltaX / (0.5 * window->GetResolution().x));
}


void Tanks::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{   
    // Add mouse button press event
    if (button == 1){
        if (tank->bullets.reload > 2){
        tank->bullets.add(new Projectile(tank->top_matrix));
        tank->bullets.reload = 0;
        }
    }
}


void Tanks::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tanks::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tanks::OnWindowResize(int width, int height)
{
}
