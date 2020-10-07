#include "AI/Mentality.h"

namespace AI
{
	Emotion::Emotion()
	{
		mState = glm::vec4(0.0f);
	}

	Mood Emotion::Expression() const
	{ 
		glm::vec4 currentState = glm::clamp(mState, glm::vec4(1), glm::vec4(0.75));

		if (MoodMap.find(currentState) != MoodMap.end())
			return MoodMap.at(currentState);

		currentState = glm::clamp(mState, glm::vec4(0.75), glm::vec4(0.5));

		if (MoodMap.find(currentState) != MoodMap.end())
			return MoodMap.at(currentState);

		currentState = glm::clamp(mState, glm::vec4(0.5), glm::vec4(0.25));

		if (MoodMap.find(currentState) != MoodMap.end())
			return MoodMap.at(currentState);

		currentState = glm::clamp(mState, glm::vec4(0.25), glm::vec4(-0.5));

		if (MoodMap.find(currentState) != MoodMap.end())
			return MoodMap.at(currentState);

		currentState = glm::clamp(mState, glm::vec4(-0.5), glm::vec4(-0.75));

		if (MoodMap.find(currentState) != MoodMap.end())
			return MoodMap.at(currentState);

		currentState = glm::clamp(mState, glm::vec4(-0.75), glm::vec4(-1));

		if (MoodMap.find(currentState) != MoodMap.end())
			return MoodMap.at(currentState);

		return Mood::NEUTRAL;
	}

	glm::vec4 Emotion::State() const
	{
		return mState;
	}

	void Emotion::Joy_Sad(const float value)
	{
		mState.x = value;
	}

	void Emotion::Trust_Disgust(const float value)
	{
		mState.y = value;
	}

	void Emotion::Fear_Anger(const float value)
	{
		mState.z = value;
	}

	void Emotion::Surprise_Anticipation(const float value)
	{
		mState.w = value;
	}
	
	Mentality::Mentality(Personality personality) : mPersonality(personality)
	{
	}
	
	Mood Mentality::CurrentMood() const
	{
		return mEmotionalState.Expression();
	}
	
	void Mentality::UpdateState(std::vector<Event> events)
	{
		glm::vec4 currentState = mEmotionalState.State();

		for (auto _event : events)
		{
			mEmotionalState.Joy_Sad					(currentState.x + mPersonality.x * _event.EmotionalImpact.x);
			mEmotionalState.Trust_Disgust			(currentState.y + mPersonality.x * _event.EmotionalImpact.y);
			mEmotionalState.Fear_Anger				(currentState.z + mPersonality.x * _event.EmotionalImpact.z);
			mEmotionalState.Surprise_Anticipation	(currentState.w + mPersonality.x * _event.EmotionalImpact.w);
		}
	}
}
