#pragma once
#include "components/simple_scene.h"
#include "components/transform.h"

namespace m1
{
    class Barca {
    public:
        glm::vec3 position;
        float rotation;

        Barca(glm::vec3 position, float rotation);
    };
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

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
        void RenderBarci(float deltaTimeSeconds);
        void RenderCorpBarca(glm::vec3 location, float rotationAngle, float deltaTimeSeconds);
        void RenderCatargBarca(glm::vec3 location, float rotationAngle, float deltaTimeSeconds);
        void RenderVeleBarca(glm::vec3 location, float rotationAngle, float deltaTimeSeconds);
        void SpawnBarci(int numarBarci);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        std::unordered_map<std::string, Texture2D*> mapTextures;
        glm::vec3 lightPosition;
        glm::vec3 lightDirection;
        float angle;
        std::vector<Barca> barci;
        float passedTime;


        // TODO(student): If you need any other class variables, define them here.

    };
}