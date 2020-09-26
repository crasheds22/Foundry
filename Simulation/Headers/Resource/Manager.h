#ifndef __MANAGER__
#define __MANAGER__

#include <map>
#include <string>

namespace Resource
{
	template<typename T>
	class Manager
	{
	public:
		~Manager()
		{
			DeleteAll();
		}

		void Create(std::string name, T obj)
		{
			mItems.insert( std::pair<std::string, T>(name, obj));
		}

		T* Retrieve(std::string name)
		{
			if(mItems.find(name) != mItems.end())
				return &mItems.at(name);

			return nullptr;
		}

	private:
		std::map<std::string, T> mItems;

		void DeleteAll()
		{
			mItems.clear();
		}
	};
}



#endif // !__MANAGER__
