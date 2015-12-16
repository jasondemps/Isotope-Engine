#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Util
{
  template <typename T>
  class Singleton
  {
  public:
    Singleton()
    {
      if (instance)
        throw;
      instance = (T*)this;
    }

    static inline T& Get()
    {
      return *instance;
    }

    virtual ~Singleton() { instance = 0; }

  protected:
    static T* instance;
  };

  template <typename T>
  T* Singleton<T>::instance = 0;
}

#endif