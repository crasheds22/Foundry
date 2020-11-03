#pragma once

#include "Resource/ResourceManager.h"

namespace Component
{
	/** @class com_Render
	 *
	 *	@brief A render component for a model and associated shader
	 *
	 *	@author Aaron Thomson
	 */
	class com_Render
	{
	public:
		/** @brief Constructor
		 */
		com_Render() { mModel = nullptr; mShader = nullptr; }
		
		/** @brief Constructor
		 *
		 *	@param modelName The name of the model to use
		 *	@param shaderName The name of the shader to use
		 */
		com_Render(std::string modelName, std::string shaderName);
		
		/** @breif Destructor
		 */
		~com_Render() { mModel = nullptr; mShader = nullptr; }

		/** @breif Returns a pointer to the model being used by this component
		 */
		Model* _Model() const;
		
		/** @brief Returns a pointer to the shader being used
		 */
		Shader* _Shader() const;

	private:
		Model* mModel = nullptr;	/*<! A pointer to a model object */
		Shader* mShader = nullptr;	/*<! A pointer to a shader object */
	};
}
