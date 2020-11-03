#ifndef __COM_AFFORDANCE_H__
#define __COM_AFFORDANCE_H__

#include <map>
#include "Affordance/Action_Qualities.h"

namespace Component 
{
	/** @class com_Affordance
	 *
	 *	@brief The Affordance Component
	 *
	 *	@author Aaron Thomson
	 */
	class com_Affordance 
	{
	public:
		/** @brief Constructor
		 */
		com_Affordance() {};
		/** @brief Constructor
		 *
		 *	@param actions A list of actions for this affordance
		 *	@param qualities A list of qualities the object would have
		 */
		com_Affordance(std::map<Affordance::Action, float> actions
					 , std::map<Affordance::Quality, float> qualities);

		/** @brief Returns the value of the action queried
		 *
		 *	@param action The action to query
		 */
		float Value(Affordance::Action action);
		
		/** @brief returns the value of the quality queried
		 *
		 *	@param quality The quality to query
		 */
		float Value(Affordance::Quality quality);

		/** @brief Updates the value of the action
		 *
		 *	@param action The action to update
		 *	@param value The value to update to
		 */
		void Update(Affordance::Action action, float value);

		/** @brief Updates the value of a quality
		 *
		 *	@param quality The quality to update
		 *	@param value The value to update to
		 */
		void Update(Affordance::Quality quality, float value);

	private:
		std::map<Affordance::Action, float>  mActionValues;		/*<! The list of actions available */
		std::map<Affordance::Quality, float> mQualityValues;	/*<! The list of qualities applied */
	};
}

#endif
