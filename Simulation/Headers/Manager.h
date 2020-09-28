#ifndef __MANAGER__
#define __MANAGER__

#include <map>
#include <string>

template<typename T>
class Manager
{
public:
	bool Create(std::string name, T obj)
	{
		if (!Find(name))
		{
			mItems.insert(std::pair<std::string, T>(name, obj));
			return true;
		}

		return false;
	}

	T* Retrieve(std::string name)
	{
		if(mItems.find(name) != mItems.end())
			return &mItems.at(name);

		return nullptr;
	}

	bool Find(std::string name)
	{
		if (mItems.find(name) != mItems.end())
			return true;

		return false;
	}

	bool DeleteItem(std::string name)
	{
		if (Find(name))
		{
			mItems.erase(mItems.find(name));
			return true;
		}

		return false;
	}

	void DeleteAll()
	{
		mItems.clear();
	}

private:
	std::map<std::string, T> mItems;
};

#endif // !__MANAGER__
