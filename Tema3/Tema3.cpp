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
    passedTime = 0;
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema3", "water.png").c_str(), GL_REPEAT);
        mapTextures["apa"] = texture;
    }

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "corp_barca.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("catarg");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "catarg_barca.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("vele");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "vele_barca.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }



    {
        Shader* shader = new Shader("Tema3Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    SpawnBarci(1);
}


void Tema3::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::SpawnBarci(int numarBarci) {
    for (int i = 0; i < numarBarci; i++) {
        glm::vec3 position = glm::vec3(0, 0.5, 1);
        Barca barca(position, 0);
        barci.push_back(barca);
    }
}

void Tema3::RenderCorpBarca(glm::vec3 location, float rotationAngle, float deltaTimeSeconds) {
    printf("%f\n", passedTime);
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, 1.f, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5 * cos(passedTime), 0.5f, (-5) * sin(passedTime)));
    modelMatrix = glm::rotate(modelMatrix, passedTime, glm::vec3(0.0f, 1.0f, 0.0f));
    RenderMesh(meshes["corp"], shaders["VertexNormal"], modelMatrix);
    
}

void Tema3::RenderBarci(float deltaTimeSeconds)
{
    for (auto& barca : barci) {
        RenderCorpBarca(barca.position, barca.rotation, deltaTimeSeconds);
        //RenderCatargBarca(barca.position, barca.rotation, deltaTimeSeconds);
        //RenderVeleBarca(barca.position, barca.rotation, deltaTimeSeconds);
    }
}


void Tema3::Update(float deltaTimeSeconds)
{
    RenderBarci(deltaTimeSeconds);
    //{
    //    glm::mat4 modelMatrix = glm::mat4(1);
    //    modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
    //    modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 1, 0));
    //    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    //}

    

    /*{
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        RenderMesh(meshes["catarg"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0.5f, 0));
        RenderMesh(meshes["vele"], shaders["VertexNormal"], modelMatrix);
    }*/

    /*{
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0.5f, 0));
        RenderSimpleMesh(meshes["plane"], shaders["Tema3Shader"], modelMatrix, mapTextures["apa"]);
    }*/
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, -3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, mapTextures["apa"]);
    }
    passedTime += deltaTimeSeconds;
}



void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}



//void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int hp)
//{
//    if (!mesh || !shader || !shader->GetProgramID())
//        return;
//
//    glUseProgram(shader->program);
//
//    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
//    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//
//    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
//    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
//    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//
//    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
//    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
//    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//
//    int loc_color = glGetUniformLocation(shader->program, "Color");
//    glUniform3fv(loc_color, 1, glm::value_ptr(color));
//
//    int loc_hp = glGetUniformLocation(shader->program, "Hp");
//    glUniform1i(loc_hp, hp);
//
//    glBindVertexArray(mesh->GetBuffers()->m_VAO);
//    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
//}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
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

    // TODO(student): Set any other shader uniforms that you need
    GLint locTime = glGetUniformLocation(shader->program, "time");

    if (mesh == meshes["sphere"])
    {
        glUniform1f(locTime, (GLfloat)Engine::GetElapsedTime());
    }
    else
    {
        glUniform1f(locTime, -1.f);
    }

    glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), false);

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        glActiveTexture(GL_TEXTURE0);
        // - bind the texture1 ID
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        // - send theuniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    if (texture2)
    {
        // TODO(student): Do these:
        // - activate texture location 1
        glActiveTexture(GL_TEXTURE1);
        // - bind the texture2 ID
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        // - send the uniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);

    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;
    float rotationSpeed = 0.8f;

}


void Tema3::OnKeyPress(int key, int mods)
{


}


void Tema3::OnKeyRelease(int key, int mods)
{

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