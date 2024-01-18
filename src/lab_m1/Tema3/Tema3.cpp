#include "lab_m1/Tema3/Tema3.h"


using namespace std;
using namespace m1;


Tema3::Tema3()
{

}


Tema3::~Tema3()
{
}


void Tema3::Init()
{   
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");
    cout<<sourceTextureDir<<endl;
    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "island.jpg").c_str(), GL_REPEAT);
        mapTextures["island"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "canvas.jpg").c_str(), GL_REPEAT);
        mapTextures["canvas"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "body.JPG").c_str(), GL_REPEAT);
        mapTextures["body"] = texture;
    }

    {
       Texture2D* texture = new Texture2D();
       texture->Load2D(PATH_JOIN(sourceTextureDir, "lighthouse1.jpg").c_str(), GL_REPEAT);
       mapTextures["lighthouse1"] = texture;
    }

    {
       Texture2D* texture = new Texture2D();
       texture->Load2D(PATH_JOIN(sourceTextureDir, "lighthouse2.jpg").c_str(), GL_REPEAT);
       mapTextures["lighthouse2"] = texture;
    }
   

    {
       Texture2D* texture = new Texture2D();
       texture->Load2D(PATH_JOIN(sourceTextureDir, "moon.jpg").c_str(), GL_REPEAT);
       mapTextures["moon"] = texture;
    }

    {
       Texture2D* texture = new Texture2D();
       texture->Load2D(PATH_JOIN(sourceTextureDir, "watter.jpg").c_str(), GL_REPEAT);
       mapTextures["watter"] = texture;
    }

    Mesh* mesh; 
    mesh = new Mesh("plane50");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("canvas");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/boat"), "canvas.obj");
    meshes[mesh->GetMeshID()] = mesh;
    
    mesh = new Mesh("stick");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/boat"), "stick.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("body");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/boat"), "body.obj");
    meshes[mesh->GetMeshID()] = mesh;
    
    mesh = new Mesh("moon");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("island");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("house");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "MyModels/cylinder"), "cylinder.obj");
    meshes[mesh->GetMeshID()] = mesh;

    //Creates a shader program
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //Sets camera
    // renderCameraTarget = false;
    // camera = new optics::Camera();
    // camera->Set(glm::vec3(0, 5, 20), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    //Remove hardcodings of parameters
    // projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    //Add boats

    for (int boat_no = 0; boat_no < 5; boat_no++){

        bool pass;
        float radius;
        do {
            radius = rand() % 12 + 3;
            pass = true;
            for (auto boat = fleet.boats.begin(); boat < fleet.boats.end(); boat++){
                if ( abs((*boat)->radius - radius) < 2 )
                {
                    pass &= false;
                }
                
            }
            cout<<pass<<endl;
        } while (!pass);


        fleet.add(new Boat(glm::mat4(1), radius));
    }
}

void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::RenderScene() {

}

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    GLint timeLocation = glGetUniformLocation(shader->program, "time");
    // TODO(student): Set any other shader uniforms that you need
    if (mesh == meshes["sphere"])
    {
        glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());
    } else
    {
        glUniform1f(timeLocation, -2.f);
    }
    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);

        // Bind the texture1 ID
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

        // Send texture uniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }



    if (texture2)
    {
        // TODO(student): Do these:
        // - activate texture location 1
        // - bind the texture2 ID
        // - send the uniform value
        glActiveTexture(GL_TEXTURE1);

        // Bind the texture2 ID
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

        // Send texture uniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);

    }

    int locationMixId=glGetUniformLocation(shader->program, "mixText");
    glUniform1i(locationMixId, mixText);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}



void Tema3::Update(float deltaTimeSeconds)
{
     //Render plane
    // cout<< "INNNNN" <<endl;
    RenderSimpleMesh(meshes["plane50"], shaders["LabShader"], glm::scale(glm::mat4(1), glm::vec3(2,1,2)),  mapTextures["watter"],mapTextures["watter"]);

    for (auto boat = fleet.boats.begin(); boat < fleet.boats.end(); boat++){
        // cout<<1<<endl;
    (*boat)->Move(deltaTimeSeconds);
    RenderSimpleMesh(meshes["body"], shaders["LabShader"], (*boat)->body_matrix,  mapTextures["body"], mapTextures["body"]);
    RenderSimpleMesh(meshes["stick"], shaders["LabShader"], (*boat)->body_matrix,  mapTextures["body"], mapTextures["body"]);
    RenderSimpleMesh(meshes["canvas"], shaders["LabShader"], (*boat)->body_matrix, mapTextures["canvas"], mapTextures["canvas"]);
    (*boat)->body_matrix = (*boat)->move_circle;
    }
    RenderSimpleMesh(meshes["moon"], shaders["LabShader"], glm::translate(glm::scale(glm::mat4(1), glm::vec3(7,7,7)), glm::vec3(-3,1,-4)), mapTextures["moon"],mapTextures["moon"]);
    RenderSimpleMesh(meshes["island"], shaders["LabShader"], glm::scale(glm::mat4(1), glm::vec3(3,1,3)),  mapTextures["island"],mapTextures["island"]);
    RenderSimpleMesh(meshes["house"], shaders["LabShader"], glm::scale(glm::mat4(1), glm::vec3(1,4,1)),  mapTextures["lighthouse1"],mapTextures["lighthouse1"]);
    RenderSimpleMesh(meshes["house"], shaders["LabShader"], glm::translate(glm::mat4(1), glm::vec3(0,4,0)),  mapTextures["lighthouse2"],mapTextures["lighthouse2"]);
    RenderSimpleMesh(meshes["house"], shaders["LabShader"], glm::translate(glm::mat4(1), glm::vec3(0,5,0)), mapTextures["lighthouse1"],mapTextures["lighthouse1"]);

}

void Tema3::FrameEnd()
{

}


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{   
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
