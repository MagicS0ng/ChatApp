#pragma once
#include "const.h"
template <typename T>
class Singleton
{
protected:
	Singleton() = default;
	Singleton(const Singleton<T>& other) = delete;
	Singleton &operator=(const Singleton<T>& other) = delete;
	static std::shared_ptr<T> _instance;
public:
	static std::shared_ptr<T> GetInstance()
	{
		static std::once_flag s_flag;
		std::call_once(s_flag, [&]()
			{
				_instance = std::shared_ptr<T>(new T);
			});
		return _instance;
	}
	void printAddress()
	{
		std::cout << _instance.get() << std::endl;
	}
	~Singleton()
	{
		std::cout << "Destruct Singlton\n";
	}
};
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;