#include "Systems/sys_Render.h"

#include "Components/com_Render.h"
#include "Components/com_Transform.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace System
{
    void sys_Render::Init()
    {
    }

    void sys_Render::Update(const Component::com_Camera* camera, const Graphics* graphics)
    {
        for (const auto& entity : mEntities)
        {
            auto& eRender    = gCoordinator.GetComponent<Component::com_Render>(entity);
            auto& eTransform = gCoordinator.GetComponent<Component::com_Transform>(entity);

            eRender._Shader()->Use();

            glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom()), graphics->AspectRatio(), 0.1f, 100.0f);
            eRender._Shader()->setMat4("projection", projection);

            glm::mat4 view = camera->ViewMatrix();
            eRender._Shader()->setMat4("view", view);

            glm::mat4 model(1.0f);
            model = glm::translate(model, eTransform.Position());
            
            model = glm::rotate(model, eTransform.Rotation().x, glm::vec3(1, 0, 0));
            model = glm::rotate(model, eTransform.Rotation().y, glm::vec3(0, 1, 0));
            model = glm::rotate(model, eTransform.Rotation().z, glm::vec3(0, 0, 1));

            model = glm::scale(model, eTransform.Scale());
            eRender._Shader()->setMat4("model", model);

            eRender._Model()->Draw(eRender._Shader()->ID());
        }
    }
}
