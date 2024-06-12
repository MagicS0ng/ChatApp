#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"
template <typename T>
class Singleton{
protected:
    Singleton()=default;
    // disable copy constructor
    Singleton(const Singleton<T> &other) = delete;
    // disable '=' operator
    Singleton & operator=(const Singleton<T>& st) = delete;
    // declare a shared_ptr,
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag; // thread security
        std::call_once(s_flag, [&](){  // lambda funtion pass s_flag by reference
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }
    void printAddress()
    {
        qDebug() << _instance.get();
    }
    ~Singleton()
    {
        qDebug()<< "this is a singleton destructor" ;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
