#pragma once

class Singleton
{
public:
	static Singleton& Instance()
	{
		static Singleton mInstance;

		return mInstance;
	}

	Singleton(const Singleton& s)	   = delete;
	void operator=(const Singleton& s) = delete;

protected:
	Singleton() {};
};
