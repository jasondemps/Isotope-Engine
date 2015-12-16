#include "assetmanager.h"
#include "..\\..\\Lua\\include\\Lua\\lua.hpp"

namespace System
{
  AssetManager::AssetManager() : baseDir("..\\..\\..\\"), assetDir(baseDir + "assets\\"), sourceDir(baseDir + "src\\"), lock(SDL_CreateMutex()), Module("assets", this)
  {
    fileSys = new FileSystem(assetDir);

    AddEntry("baseDir", baseDir.c_str());
    AddEntry("assetDir", assetDir.c_str());
    AddEntry("sourceDir", sourceDir.c_str());

    PushEntries();

    // Load a test texture for now.
    NewAsset<ImageAsset>(std::string("textest"), std::string(assetDir + "img\\" + "textest.png"));
  }

  AssetManager::~AssetManager()
  {
    for (auto a : assets)
      delete a.second;

    assets.clear();

    delete fileSys;

    SDL_DestroyMutex(lock);
  }

  void AssetManager::GetExtensions()
  {
    // Create a new lua instance so we can read the extensions
    //lua_State* l = luaL_newstate();
    //luaL_dofile(l, (assetDir + "extensions.lua").c_str());


  }

  void AssetManager::LoadFiles()
  {
    /*
    // Traverse our filesystem while we can
    while (fileSys->Next())
    {
      auto dir = fileSys->Enumerate();

      // How are we going to handle types here....
      for (auto& f : dir)
        NewAsset<>(f.first, f.second);
    }
    */
  }
}