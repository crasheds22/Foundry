#ifndef __MENTALITY_H__
#define __MENTALITY_H__

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
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

	class Emotion
	{
	public:
		Emotion(float js = 0.0f, float td = 0.0f, float fa = 0.0f, float sa = 0.0f);

		Mood Expression() const;

	private:
		glm::vec4 mState;

		std::map<glm::vec4, Mood> mMoodMap;
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
