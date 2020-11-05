#pragma once

#include "Graphics/Graphics.h"
#include "Resource/ResourceManager.h"
#include "Props.h"

#include "Manager.h"
#include "Singleton.h"

#include "Stage.h"

#include "Components/Components.h"

/** @class Thatre 
 *
 *	@brief The game controller, holds all the scenes in the game and runs through them one at a time
 *
 *	@author Aaron Thomson
 */
class Theatre
	: public Singleton<Theatre>
{
public:
	/** @brief Constructor
	 */
	Theatre();
	
	/** @brief Destructor
	 */
	~Theatre();

	/** @brief Pre level setup
	 */
	void PreShow();

	/** @brief Runs the active level 
	 */
	void PlayShow();

	/** @brief Packup and close down of the app
	 */
	void EndShow();

private:
	Graphics* mGraphics;	/*!< Active graphics context */

	Resource::ResourceManager* mResourceManager;	/*!< Pointer to the resource manager */
		
	Props* mProps;	/*!< Pointer to the props */

	Stage mActiveStage;	/*!< The active stage in the game */
};

