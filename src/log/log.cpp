#include "log.h"
#include "..\\system\\modulehandler.h"

#include <string>
#include <iostream>
#include <fstream>

namespace System
{
  Log::Log(const char* file) : Module("log", this), fileStream(file)
  {
    AddEntry("PrintError", Log::PrintError);
    AddEntry("PrintDebug", Log::PrintDebug);
    AddEntry("PrintInfo", Log::PrintInfo);
    AddEntry("DumpGameTable", Log::DumpGameTableLua);

    PushEntries();
  }

  void Log::PrintError(const char* msg)
  {
    ToConsole(std::string("Error: ") + msg);
  }

  void Log::PrintDebug(const char* msg)
  {
    ToConsole(std::string("Debug: ") + msg);
  }

  void Log::PrintInfo(const char* msg)
  {
    ToFile(std::string("Info: ") + msg);
  }

  int Log::PrintError(lua_State* l)
  {
    ModuleHandler::Get().GetModule("log")->GetParentAs<Log*>()->ToConsole(std::string("Error: ") + luaL_checkstring(l, -1));

    return 0;
  }

  int Log::PrintDebug(lua_State* l)
  {
    ModuleHandler::Get().GetModule("log")->GetParentAs<Log*>()->ToConsole(std::string("Debug: ") + luaL_checkstring(l, -1));

    return 0;
  }

  int Log::PrintInfo(lua_State* l)
  {
    ModuleHandler::Get().GetModule("log")->GetParentAs<Log*>()->ToFile(std::string("Info: ") + luaL_checkstring(l, -1));

    return 0;
  }

  int Log::DumpGameTableLua(lua_State* l)
  {
    ModuleHandler::Get().DumpInfo();

    return 0;
  }

  void Log::DumpGameTable()
  {
    ModuleHandler::Get().DumpInfo();
    //ToFile(ModuleHandler::Get().DumpInfo());
  }

  void Log::ToConsole(std::string const & msg) const
  {
    std::cout << msg << std::endl;
  }

  void Log::ToFile(std::string const & msg)
  {
    // Probably doesn't work.
    fileStream.write(msg.c_str(), fileStream.end);
  }

  Log::~Log()
  {
    fclose(stdout);
  }
}