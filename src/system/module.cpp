#include "module.h"

namespace System
{
  Module::Module(const char* name, void* parent, bool useLua_) : useLua(useLua_), moduleParent(parent), mName(name) 
  {}

  void Module::AddEntry(const char* name, double value)
  {
    entries.push_back(new EntryNumber(name, value));
  }
  
  void Module::AddEntry(const char* name, bool value)
  {
    entries.push_back(new EntryBoolean(name, value));
  }
  
  void Module::AddEntry(const char* name, lua_CFunction value)
  {
    entries.push_back(new EntryFunction(name, value));
  }

  // String
  void Module::AddEntry(const char* name, const char* value)
  {
    entries.push_back(new EntryString(name, value));
  }

  // Table
  void Module::AddEntry(const char* name, std::vector<Entry*>& vec)
  {
    entries.push_back(new EntryTable(name, vec));
  }

  std::vector<Entry*>& Module::GetEntries()
  {
    return entries;
  }

  const char* Module::GetName() const
  {
    return mName;
  }

  void Module::PushEntries()
  {
    ModuleHandler::Get().RegisterModule(*this);
  }

  void Module::RemoveEntries()
  {
    for (auto e : entries)
      delete e;

    entries.clear();
  }

  Module::~Module()
  {
    RemoveEntries();
  }
}