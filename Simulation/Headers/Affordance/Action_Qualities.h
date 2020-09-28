#ifndef __ACTION_QUALITIES__
#define __ACTION_QUALITIES__

namespace Affordance
{
	enum class Action {
		SIT,
		THROW,
		PICK_UP,
		PUSH,
		PULL,
		EAT,
		TALK
	};

	enum class Quality {
		HEAVY,
		LIGHT,
		DIRTY,
		IMMOVABLE,
		SMELLY,
		PLEASANT,
		ROTTEN
	};
}

#endif
