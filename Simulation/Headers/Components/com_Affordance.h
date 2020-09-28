#ifndef __COM_AFFORDANCE__
#define __COM_AFFORDANCE__

#include <unordered_map>
#include "Affordance/Action_Qualities.h"

namespace Component {
	class com_Affordance {
	public:
		com_Affordance() {};

		void InsertAction(Affordance::Action act, float val = 0.0f);
		float CheckAction(Affordance::Action act);

		void InsertQuality(Affordance::Quality qual, float val = 0.0f);
		float CheckQuality(Affordance::Quality qual);

	private:
		std::unordered_map<Affordance::Action, float> mActionMap;
		std::unordered_map<Affordance::Quality, float> mQualityMap;
	};
}

#endif
