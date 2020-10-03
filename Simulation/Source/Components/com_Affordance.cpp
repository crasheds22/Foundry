#include "Components/com_Affordance.h"

namespace Component 
{
	com_Affordance::com_Affordance(std::map<Affordance::Action, float> actions, std::map<Affordance::Quality, float> qualities)
	{
		mActionValues = actions;
		mQualityValues = qualities;
	}

	float com_Affordance::Value(Affordance::Action action)
	{
		return mActionValues[action];
	}

	float com_Affordance::Value(Affordance::Quality quality)
	{
		return mQualityValues[quality];
	}

	void com_Affordance::Update(Affordance::Action action, float value)
	{
		mActionValues[action] = value;
	}

	void com_Affordance::Update(Affordance::Quality quality, float value)
	{
		mQualityValues[quality] = value;
	}
}
