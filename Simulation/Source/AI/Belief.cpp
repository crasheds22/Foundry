#include "AI/Belief.h"

namespace AI {
	void Belief::Insert(Affordance::Action action, Affordance::Quality quality, int value) {
		actionEval[action][quality] = value;
	}

	int Belief::Get(Affordance::Action action, Affordance::Quality quality) {
		return(actionEval[action][quality]);
	}
}