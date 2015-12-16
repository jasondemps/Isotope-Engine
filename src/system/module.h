#ifndef MODULE_H_
#define MODULE_H_

#include "Lua\lua.hpp"
#include "moduleentry.h"
#include "modulehandler.h"

#include <vector>

namespace System
{
  class Module
  {
  public:
    Module(const char* name, void* parent, bool useLua = true);
    ~Module();

    // Add integer
    void AddEntry(const char* name, double value);
    // Add boolean
    void AddEntry(const char* name, bool value);
    // Add function
    void AddEntry(const char* name, lua_CFunction value);
    // Add string
    void AddEntry(const char* name, const char* value);
    // Add table
    void AddEntry(const char* name, std::vector<Entry*>& vec); // Wish this could be variadic...

    // This must be called to actually register everything with the lua state!
    void PushEntries();

    void RemoveEntries();

    std::vector<Entry*>& GetEntries();
    const char* GetName() const;
    template <typename T>
    T GetParentAs() const 
    {
      return reinterpret_cast<T>(moduleParent);
    }

  protected:
    void* moduleParent;
    std::vector<Entry*> entries;
    bool useLua;
    const char* mName;
  };
}

#endif