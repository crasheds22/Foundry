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

	Singleton(const T& s)	   = delete;
	void operator=(const T& s) = delete;

protected:
	Singleton() {};
};
