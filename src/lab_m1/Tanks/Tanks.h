#pragma once

#include "camera/lab_camera.h"
#include "components/simple_scene.h"
#include "game_obj/Enemies.h"
#include "camera_3p.h"
#include <vector>
#include <string>
#include <iostream>

namespace m1
{
    class Tanks : public gfxc::SimpleScene
    {
     public:

        Tanks();
        ~Tanks();

        void Init() override;


         void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color);
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
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color, unsigned int health);
        

        void RenderScene();
     protected:

        //Game objects
        Tank* tank;
        Buildings braffles;
        float game_time;        
        Enemies enemies;

        //Light
        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        //Camera
        cam::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        int score;
        bool ended; 

    };
}   // namespace m1

