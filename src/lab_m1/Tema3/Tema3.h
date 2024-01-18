#pragma once


#include "components/simple_scene.h"
#include "camera/lab_camera.h"
#include <string>
#include <unordered_map>
#include "components/transform.h"


#include "game_obj/Fleet.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
     public:

        Tema3();
        ~Tema3();

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
        void RenderScene();
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D *texture1 = NULL, Texture2D *texture2 = NULL);
        Texture2D *CreateRandomTexture(unsigned int width, unsigned int height);

     protected:
     //Light
        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
      //Camera
        optics::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
      //
      Fleet fleet;
      std::unordered_map<std::string, Texture2D *> mapTextures;
      int mixText=0;
    };
}  

