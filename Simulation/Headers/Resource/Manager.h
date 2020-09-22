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

		void Create(std::string name, T& obj)
		{
			mItems[name] = obj;
		}

		T* Retrieve(std::string name)
		{
			return &mItems[name];
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
