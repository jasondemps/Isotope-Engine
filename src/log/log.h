#ifndef LOG_H_
#define LOG_H_

#include "..\\system\\module.h"
#include "..\\patterns\\singleton.hpp"
#include "..\\system\\messagehandle.h"

#include <iostream>
#include <fstream>

namespace System
{
  struct Log : public Module, public MessageHandle
  {
    Log(const char* file = "out.txt");
    ~Log();

    void DumpGameTable();
    static int DumpGameTableLua(lua_State* l);

    void PrintError(const char*);
    void PrintDebug(const char*);
    void PrintInfo(const char*);

    // Lua calls
    static int PrintError(lua_State* l);
    static int PrintDebug(lua_State* l);
    static int PrintInfo(lua_State* l);

    void BroadcastMessage(Message* msg) {}

  private:
    void ToConsole(std::string const & msg) const;
    void ToFile(std::string const & msg);

    std::ofstream fileStream;
  };
}

#endif