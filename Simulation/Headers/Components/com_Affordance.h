#ifndef __COM_AFFORDANCE__
#define __COM_AFFORDANCE__

#include <vector>
#include "Affordance/Action_Qualities.h"

namespace Component {
	class com_Affordance {
	public:
		com_Affordance() {};
		com_Affordance(std::vector<Affordance::Action>& act, std::vector<Affordance::Quality>& qual);

		void InsertAction(int i, Affordance::Action act);
		void InsertAction(Affordance::Action act);
		const Affordance::Action GetAction(int i);

		void InsertQuality(int i, Affordance::Quality qual);
		void InsertQuality(Affordance::Quality qual);
		const Affordance::Quality GetQuality(int i);
	private:
		std::vector<Affordance::Action> mActions;
		std::vector<Affordance::Quality> mQualities;
	};
}

#endif
