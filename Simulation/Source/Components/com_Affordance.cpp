#include "Components/com_Affordance.h"

namespace Component {
	void com_Affordance::InsertAction(Affordance::Action act, float val) {
		mActionMap[act] = val;
	}

	float com_Affordance::CheckAction(Affordance::Action act) {
		return(mActionMap[act]);
	}

	void com_Affordance::InsertQuality(Affordance::Quality qual, float val) {
		mQualityMap[qual] = val;
	}

	float com_Affordance::CheckQuality(Affordance::Quality qual) {
		return(mQualityMap[qual]);
	}
}
