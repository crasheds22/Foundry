#pragma once

#include "Resource/ResourceManager.h"

/**	\namespace Component
 *
 *	The namespace all Components are located in.
 */
namespace Component
{
	class com_Render
	{
	public:
		/**
		*	\brief Default constructor
		* 
		*	Not to be used by the user
		* 
		*	\post com_Render is constructed
		*/
		com_Render() { mModel = nullptr; mShader = nullptr; }
		/**
		*	\brief Constructor
		* 
		*	\param [in] modelName	filename of the model
		*	\param [in] shaderName	filename of the shader
		* 
		*	\post com_Render is constructed
		*/
		com_Render(std::string modelName, std::string shaderName);
		/**
		*	\brief Destructor
		* 
		*	\post com_Render is destructed
		*/
		~com_Render() { mModel = nullptr; mShader = nullptr; }

		/**
		*	\brief mModel accessor
		* 
		*	\return mModel
		*/
		Model* _Model() const;
		/**
		*	\brief mShader accessor
		* 
		*	\return mShader
		*/
		Shader* _Shader() const;

	private:
		Model* mModel;		/*!< Model variable*/
		Shader* mShader;	/*!< Shader variable*/
	};
}
