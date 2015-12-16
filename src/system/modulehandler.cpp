#include "modulehandler.h"
#include "module.h"

#include "..\\resources\\assetmanager.h"

#include <iostream>

namespace System
{
  ModuleHandler::ModuleHandler() : /* assetManager(assetManager), mScriptDir(assetManager->NewAsset<DirAsset>(std::string("scripts"), assetManager->GetSource() + "scripts\\")), */mState(luaL_newstate())
  {
    luaL_openlibs(mState);

    lua_newtable(mState);

    lua_setglobal(mState, mGlobalName = "Game");
  }
  
  void ModuleHandler::Initialize(AssetManager* assetManager_)
  {
    assetManager = assetManager_;
    mScriptDir = assetManager->NewAsset<DirAsset>(std::string("scripts"), assetManager->GetSource() + "scripts\\");
  }

  lua_State* ModuleHandler::GetState() const
  {
    return mState;
  }

  const char* ModuleHandler::GetGlobalName() const 
  {
    return mGlobalName;
  }

  void ModuleHandler::RegisterModule(Module& module)
  {
    // Store the module, we might need it later.
    mModules.insert(std::make_pair(module.GetName(), &module));

    // Get the global "Game" table
    lua_getglobal(mState, mGlobalName);

    // Create a new nested table
    lua_pushstring(mState, module.GetName());
    lua_newtable(mState);

    // Push all entries into the current Lua table.
    for (auto e : module.GetEntries())
    {
      ProcessEntry(e);
      lua_settable(mState, -3);
    }

    // Push new stuff into the global table
    lua_settable(mState, -3);
    lua_setglobal(mState, mGlobalName);
  }

  void ModuleHandler::ProcessEntry(Entry* entry)
  {
    // Set the key
    lua_pushstring(mState, entry->name);

    // Set the value, based off the type of Entry
    switch(entry->type)
    {
    case number:
      lua_pushnumber(mState, entry->asNumber());
      break;
        
    case boolean:
      lua_pushboolean(mState, entry->asBoolean());
      break;

    case function:
      lua_pushcfunction(mState, entry->asFunction());
      break;

    case string:
      lua_pushstring(mState, entry->asString());
      break;

    case table:
      entry->asTable(mState);
      break;
    }
  }

  void ModuleHandler::DumpInfo()
  {
    if (LoadFile(mScriptDir->data + "dump.lua") != 0)
      std::cout << "Something went terribly wrong! " << GetError() << std::endl;

    if (lua_isstring(mState, -1))
      std::cout << lua_tostring(mState, -1) << std::endl;
      //return lua_tostring(mState, -1);
  }

  int ModuleHandler::ExecuteScriptMain()
  {
    int returnCode = 0; // Default, which is good
    int loopEval = 0; // Default = false
    int continueError = 0; // Default = false

    // load config.lua, to setup basic stuff and have a variable pointing to our main entry point.
    if (LoadFile(mScriptDir->data + "config.lua") != 0)
      returnCode = GetError();

    // Check if we want to Re-Evaluate even if theres an error.
    lua_getglobal(mState, "ContinueOnError");
    continueError = lua_toboolean(mState, -1);

    // Get the LoopEval variable, to see if we want to evaluate indefinitely
    lua_getglobal(mState, "LoopEval");
    loopEval = lua_toboolean(mState, -1);

    // Get the global mainfile variable, which points to the main entry of our lua code
    lua_getglobal(mState, "MainFile");
    const char* mainFile = lua_tostring(mState, -1);
    if (LoadFile(mScriptDir->data + mainFile) != 0)
      returnCode = GetError();

    lua_getglobal(mState, "package.path");

    // Look for a main, then execute it!
    lua_getglobal(mState, "lua_main");

    if (lua_pcall(mState, 0, 1, 0))
      returnCode = GetError();

    return continueError || returnCode == 0 && loopEval;
  }

  int ModuleHandler::LoadFile(std::string path)
  {
    // Load a file into lua, return an error code if we can't.
    if (luaL_dofile(mState, path.c_str()))
    {
      std::cout << "Lua: Couldn't load " << path << std::endl;
      return -1;
    }

    return 0;
  }

  int ModuleHandler::GetError()
  {
    // Return the return code from lua_main, or look for an error string.
    if (lua_isnumber(mState, -1))
      return (int) lua_tonumber(mState, -1);
    else if (lua_isstring(mState, -1))
    {
      std::cout << "Lua Error: " << lua_tostring(mState, -1) << std::endl;
      return -1;
    }

    return 0; // No error
  }

  Module* ModuleHandler::GetModule(const char* name)
  {
    auto m = mModules.find(name);

    return m != mModules.end() ? m->second : nullptr;
  }

  ModuleHandler::~ModuleHandler()
  {
    lua_close(mState);
  }
}