#pragma once

#include <glm/glm.hpp>

namespace AI {
	enum class Mood {
		SERENITY,
		JOY,
		LOVE,
		ACCEPTANCE,
		TRUST,
		SUBMISSION,
		APPREHENSION,
		FEAR,
		AWE,
		DISTRACTION,
		SURPRISE,
		DISAPPROVAL,
		PENSIVE,
		SADNESS,
		REMORSE,
		BOREDOM,
		DISGUST,
		CONTEMPT,
		ANNOYANCE,
		ANGER,
		AGGRESSIVENESS,
		INTEREST,
		ANTICIPATION,
		OPTIMISM
	};

	struct Emotion {
		float ecstasy;
		float admiration;
		float terror;
		float amazement;
		float grief;
		float loathing;
		float rage;
		float vigilance;
	};

	struct Personality {
		float stability;
		float version;
	};
}

	