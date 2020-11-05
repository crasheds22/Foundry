#pragma once

/** @class Singleton
 *
 *	@brief Sets a class to follow the singleton pattern
 *
 *	@author Aaron Thomson 
 */
template<typename T>
class Singleton
{
public:
	/** @brief Static function returning a reference to the static object
	 */
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
