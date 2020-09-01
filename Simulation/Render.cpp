#include "Render.h"

extern ECS::Coordinator gCoordinator;

namespace System
{
	Render::Render()
	{
	}

	void Render::Update(float dt)
	{
		for (const auto& entity : mEntities)
		{
			auto& model  = gCoordinator.GetComponent<Component::Model>(entity);
			auto& shader = gCoordinator.GetComponent<Component::Shader>(entity);

			shader.Use();


		}
	}
}
