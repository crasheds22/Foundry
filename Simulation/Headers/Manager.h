#ifndef __MANAGER__
#define __MANAGER__

#include <map>
#include <string>

/** @class Manager
 *
 *	@brief Template class for managing items
 *
 *	@author Aaron Thomson
 */
template<typename T>
class Manager
{
public:
	/** @brief Inserts an object into the backing map
	 */
	bool Create(std::string name, T obj)
	{
		if (!Find(name))
		{
			mItems.insert(std::pair<std::string, T>(name, obj));
			return true;
		}

		return false;
	}

	/** @brief Returns an object specified by the name
	 */
	T* Retrieve(std::string name)
	{
		if(mItems.find(name) != mItems.end())
			return &mItems.at(name);

		return nullptr;
	}

	/** @brief Returns true if the object searched for is found
	 */
	bool Find(std::string name)
	{
		if (mItems.find(name) != mItems.end())
			return true;

		return false;
	}

	/** @brief Deletes the item if found in the backing map
	 */
	bool DeleteItem(std::string name)
	{
		if (Find(name))
		{
			mItems.erase(mItems.find(name));
			return true;
		}

		return false;
	}

	/** @brief Deletes all object from the backing map
	 */
	void DeleteAll()
	{
		mItems.clear();
	}

private:
	std::map<std::string, T> mItems;	/*!< The backing map */
};

#endif // !__MANAGER__
