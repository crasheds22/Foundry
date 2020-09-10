#include "sys_Render.h"

#include "com_Model.h"
#include "com_Shader.h"
#include "com_Transform.h"

#include "Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include "Graphics.h"
extern Graphics gGraphics;

namespace System
{
    void sys_Render::Init()
    {
    }

    void sys_Render::Update(Component::com_Camera& camera)
    {
        for (const auto& entity : mEntities)
        {
            auto& eModel = gCoordinator.GetComponent<Component::com_Model>(entity);
            auto& eShader = gCoordinator.GetComponent<Component::com_Shader>(entity);
            auto& eTransform = gCoordinator.GetComponent<Component::com_Transform>(entity);

            eShader.Use();

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom()), gGraphics.AspectRatio(), 0.1f, 100.0f);
            eShader.setMat4("projection", projection);

            glm::mat4 view = camera.ViewMatrix();
            eShader.setMat4("view", view);

            glm::mat4 model(1.0f);
            model = glm::translate(model, eTransform.Position());
            
            model = glm::scale(model, eTransform.Scale());
            eShader.setMat4("model", model);

            eModel.Draw(eShader.ID());
        }
    }
}
