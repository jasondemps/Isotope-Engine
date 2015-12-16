#include "moduleentry.h"
#include "modulehandler.h"

#include <functional>

namespace System
{
  // As Number
  EntryNumber::EntryNumber(const char* name_, double val) : Entry(name_), data(val)
  { 
    type = number; 
  }

  lua_Number EntryNumber::asNumber() { return data; }

  // As Boolean
  EntryBoolean::EntryBoolean(const char* name_, bool val) : Entry(name_), data(val)
  { 
    type = boolean;
  }

  int EntryBoolean::asBoolean() { return data; }

  // As String
  EntryString::EntryString(const char* name_, const char* val) : Entry(name_), data(val)
  { 
    type = string; 
  }

  const char* EntryString::asString() { return data; }

  // As Table
  EntryTable::EntryTable(const char* name_, std::vector<Entry*>& vec) : Entry(name_), data(vec)
  { 
    type = table; 
  }

  void EntryTable::asTable(lua_State* state)
  {
    lua_newtable(state);

    // Iterate through the key/values, call back to 'RegisterModule' on each key and value to store'em
    // Should make this tail-recursive maybe?....future.....
    for (unsigned i = 0; i < data.size(); ++i)
    {
      // Pass the next entry onto the Lua Stack.
      ModuleHandler::Get().ProcessEntry(data[i]);
      lua_settable(state, -3);
    }
  }

  // As Function
  EntryFunction::EntryFunction(const char* name_, lua_CFunction val) : Entry(name_), data(val)
  { 
    type = function; 
  }

  lua_CFunction EntryFunction::asFunction() 
  { 
    return data; 
  }
}