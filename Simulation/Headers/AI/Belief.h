#ifndef __BELIEF__
#define __BELIEF__

#include <map>

#include "Affordance/Action_Qualities.h"

namespace AI
{
	class Belief
	{
	public:
		void Insert(Affordance::Action action, Affordance::Quality quality, int value);
	private:
		std::map<Affordance::Action, std::map<Affordance::Quality, int>> actionEval{};
	};
}

#endif
