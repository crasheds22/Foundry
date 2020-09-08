#include "sys_Render.h"

#include "../ECS_core/Coordinator.h"
extern ECS::Coordinator mCoordinator;

namespace System
{
	Render::Render()
	{
	}

	void Render::Update()
	{
		for (const auto& entity : mEntities)
		{
			auto eModel = mCoordinator.GetComponent<Component::Model>(entity);
			auto eShader = mCoordinator.GetComponent<Component::Shader>(entity);
			auto eTransform = mCoordinator.GetComponent<Component::Transform>(entity);

			eShader.Use();

			glm::mat4 projection = glm::perspective(glm::radians(Props::GetActiveCamera()->Zoom()), _Graphics::AspectRatio(), 0.1f, 100.0f);
			eShader.setMat4("projection", projection);

			glm::mat4 view = Props::GetActiveCamera()->ViewMatrix();
			eShader.setMat4("view", view);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, eTransform.Position());

			model = glm::rotate(model, glm::length(eTransform.Rotation()), glm::normalize(eTransform.Rotation()));

			model = glm::scale(model, eTransform.Scale());
			eShader.setMat4("model", model);

			eModel.Draw(eShader.ID());
		}
	}
}
