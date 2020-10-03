#ifndef __COM_AFFORDANCE_H__
#define __COM_AFFORDANCE_H__

#include <map>
#include "Affordance/Action_Qualities.h"

namespace Component 
{
	class com_Affordance 
	{
	public:
		com_Affordance() {};
		com_Affordance(std::map<Affordance::Action, float> actions
					 , std::map<Affordance::Quality, float> qualities);

		float Value(Affordance::Action action);
		float Value(Affordance::Quality quality);

		void Update(Affordance::Action action, float value);
		void Update(Affordance::Quality quality, float value);

	private:
		std::map<Affordance::Action, float>  mActionValues;
		std::map<Affordance::Quality, float> mQualityValues;
	};
}

#endif
