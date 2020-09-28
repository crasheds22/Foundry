#pragma once

template<typename T>
class Singleton
{
public:
	static T& Instance()
	{
		static T mInstance;

		return mInstance;
	}

	Singleton(const Singleton& s)	   = delete;
	void operator=(const Singleton& s) = delete;

protected:
	Singleton() {};
};
