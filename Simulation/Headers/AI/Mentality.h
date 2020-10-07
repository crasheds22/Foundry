#ifndef __MENTALITY_H__
#define __MENTALITY_H__

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/common.hpp>
#include <map>
#include <vector>

namespace AI
{
	using Personality = glm::vec2;

	enum class Mood
	{
		SERENITY	, JOY			, ECSTASY	, LOVE,
		ACCEPTANCE	, TRUST			, ADMIRATION, SUBMISSION, 
		APPREHENSION, FEAR			, TERROR	, AWE,
		DISTRACTION	, SURPRISE		, AMAZEMENT	, DISAPPROVAL,
		PENSIVENESS	, SADNESS		, GRIEF		, REMORSE,
		BOREDOM		, DISGUST		, LOATHING	, CONTEMPT, 
		ANNOYANCE	, ANGER			, RAGE		, AGRESSION,
		INTEREST	, ANTICIPATION	, VIGILANCE	, OPTIMISM,
		NEUTRAL
	};

	std::map<glm::vec4, Mood> MoodMap =
	{
		{ glm::vec4(0.25, 0, 0, 0), Mood::SERENITY },
		{ glm::vec4(0.50, 0, 0, 0), Mood::JOY },
		{ glm::vec4(0.75, 0, 0, 0), Mood::ECSTASY },

		{ glm::vec4(0.25, 0.25, 0, 0), Mood::LOVE },
		{ glm::vec4(0.75, 0.75, 0, 0), Mood::LOVE },
		
		{ glm::vec4(0, 0.25, 0, 0), Mood::ACCEPTANCE },
		{ glm::vec4(0, 0.50, 0, 0), Mood::TRUST },
		{ glm::vec4(0, 0.75, 0, 0), Mood::ADMIRATION },

		{ glm::vec4(0, 0.25, 0.25, 0), Mood::SUBMISSION },
		{ glm::vec4(0, 0.75, 0.75, 0), Mood::SUBMISSION },

		{ glm::vec4(0, 0, 0.25, 0), Mood::APPREHENSION },
		{ glm::vec4(0, 0, 0.50, 0), Mood::FEAR },
		{ glm::vec4(0, 0, 0.75, 0), Mood::TERROR },

		{ glm::vec4(0, 0, 0.25, 0.25), Mood::AWE },
		{ glm::vec4(0, 0, 0.75, 0.75), Mood::AWE },

		{ glm::vec4(0, 0, 0, 0.25), Mood::DISTRACTION },
		{ glm::vec4(0, 0, 0, 0.50), Mood::SURPRISE },
		{ glm::vec4(0, 0, 0, 0.75), Mood::AMAZEMENT },

		{ glm::vec4(-0.25, 0, 0, 0.25), Mood::DISAPPROVAL },
		{ glm::vec4(-0.75, 0, 0, 0.75), Mood::DISAPPROVAL },

		{ glm::vec4(-0.25, 0, 0, 0), Mood::PENSIVENESS },
		{ glm::vec4(-0.50, 0, 0, 0), Mood::SADNESS },
		{ glm::vec4(-0.75, 0, 0, 0), Mood::GRIEF },

		{ glm::vec4(-0.25, -0.25, 0, 0), Mood::REMORSE },
		{ glm::vec4(-0.75, -0.75, 0, 0), Mood::REMORSE },

		{ glm::vec4(0, -0.25, 0, 0), Mood::BOREDOM },
		{ glm::vec4(0, -0.50, 0, 0), Mood::DISGUST },
		{ glm::vec4(0, -0.75, 0, 0), Mood::LOATHING },

		{ glm::vec4(0, -0.25, -0.25, 0), Mood::CONTEMPT},
		{ glm::vec4(0, -0.75, -0.75, 0), Mood::CONTEMPT},

		{ glm::vec4(0, 0, -0.25, 0), Mood::ANNOYANCE },
		{ glm::vec4(0, 0, -0.50, 0), Mood::ANGER },
		{ glm::vec4(0, 0, -0.75, 0), Mood::RAGE },

		{ glm::vec4(0, 0, -0.25, -0.25), Mood::AGRESSION },
		{ glm::vec4(0, 0, -0.75, -0.75), Mood::AGRESSION },

		{ glm::vec4(0, 0, 0, -0.25), Mood::INTEREST },
		{ glm::vec4(0, 0, 0, -0.50), Mood::ANTICIPATION },
		{ glm::vec4(0, 0, 0, -0.75), Mood::VIGILANCE },

		{ glm::vec4(0.25, 0, 0, -0.25), Mood::OPTIMISM },
		{ glm::vec4(0.75, 0, 0, -0.75), Mood::OPTIMISM },

		{ glm::vec4(0, 0, 0, 0), Mood::NEUTRAL }
	};

	class Emotion
	{
	public:
		Emotion();

		Mood Expression() const;

		glm::vec4 State() const;
		void Joy_Sad				(const float value);
		void Trust_Disgust			(const float value);
		void Fear_Anger				(const float value);
		void Surprise_Anticipation	(const float value);

	private:
		glm::vec4 mState;

	};

	struct Event
	{
		glm::vec4 EmotionalImpact;
	};

	class Mentality
	{
	public:
		Mentality(Personality personality);

		Mood CurrentMood() const;

		void UpdateState(std::vector<Event> events);

	private:
		Personality mPersonality;

		Emotion mEmotionalState;
	};
}

#endif
