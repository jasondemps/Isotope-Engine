#ifndef MODULEHANDLER_H_
#define MODULEHANDLER_H_

#include "Lua\\lua.hpp"
#include "..\\patterns\\singleton.hpp"
#include "..\\system\\messagehandle.h"

#include <string>
#include <unordered_map>

namespace System
{
  class Module;
  struct Entry;
  class AssetManager;
  struct DirAsset;

  class ModuleHandler : public Util::Singleton<ModuleHandler>, public MessageHandle
  {
  public:
    ModuleHandler(/*AssetManager* assetManager*/);
    ~ModuleHandler();

    void Initialize(AssetManager* assetManager);

    // Register Modules/Entries with Lua
    void ProcessEntry(Entry* entry);
    void RegisterModule(Module& module);
    
    // Debug / Error Facilities
    void DumpInfo();
    int GetError();

    void BroadcastMessage(Message* msg) {}

    // Execute our lua main entry point
    int ExecuteScriptMain(); // Should add a way to pass arguments here....would be great to have variadics...

    // Get private stuff
    Module* GetModule(const char* name);
    lua_State* GetState() const;
    const char* GetGlobalName() const;

    // Helpers/Conveniences
    int LoadFile(std::string path);

  private:
    AssetManager* assetManager;
    std::unordered_map<const char*, Module*> mModules;
    DirAsset* mScriptDir;
    lua_State* mState;
    const char* mGlobalName;
  };
}

#endif