#include "Components/com_Affordance.h"

namespace Component {
	com_Affordance::com_Affordance(std::vector<Affordance::Action>& act, std::vector<Affordance::Quality>& qual) {
		mActions = act;
		mQualities = qual;
	}

	void com_Affordance::InsertAction(int i, Affordance::Action act) {
		mActions[i] = act;
	}

	void com_Affordance::InsertAction(Affordance::Action act) {
		mActions.push_back(act);
	}

	const Affordance::Action com_Affordance::GetAction(int i) {
		return(mActions[i]);
	}

	void com_Affordance::InsertQuality(int i, Affordance::Quality qual) {
		mQualities[i] = qual;
	}

	void com_Affordance::InsertQuality(Affordance::Quality qual) {
		mQualities.push_back(qual);
	}

	const Affordance::Quality com_Affordance::GetQuality(int i) {
		return(mQualities[i]);
	}
}