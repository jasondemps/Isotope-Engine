#ifndef MODULEENTRY_H_
#define MODULEENTRY_H_

#include "Lua\lua.hpp"

#include <vector>

namespace System
{
  enum LuaType { boolean, number, string, function, userdata, table };

  struct Entry
  {
    Entry(const char* name_) : name(name_) {}

    virtual lua_Number asNumber() { return 0; }
    virtual int asBoolean() { return 0; }
    virtual lua_CFunction asFunction() { return 0; }
    virtual const char* asString() { return 0; }
    virtual void asTable(lua_State* state) {}

    LuaType type;
    const char* name;
  };

  struct EntryNumber : public Entry
  {
    EntryNumber(const char* name_, double val);
    lua_Number asNumber();

    double data;
  };

  struct EntryBoolean : public Entry
  {
    EntryBoolean(const char* name_, bool val);
    int asBoolean();

    int data;
  };

  struct EntryString : public Entry
  {
    EntryString(const char* name_, const char* val);
    const char* asString();

    const char* data; 
  };

  struct EntryTable : public Entry
  {
    EntryTable(const char* name_, std::vector<Entry*>& vec);
    void asTable(lua_State* state);
    
    std::vector<Entry*> data;
  };

  struct EntryFunction : public Entry
  {
    EntryFunction(const char* name_, lua_CFunction val);
    lua_CFunction asFunction();

    lua_CFunction data;
  };
}

#endif