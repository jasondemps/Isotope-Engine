#ifndef ASSETMANAGER_H_
#define ASSETMANAGER_H_

#include "asset.h"
#include "..\\patterns\\singleton.hpp"
#include "..\\resources\\filesystem.h"
#include "..\\system\\messagehandle.h"
#include "..\\system\\module.h"

#include <iostream>
#include <SDL\\SDL.h>
#include <cstring>
#include <vector>
#include <map>

// Lets handle some automatic asset loading!
// We need to get a list of extensions to look for though...
// Lets use lua to read in extensions

namespace System
{
  class AssetManager : public MessageHandle, public Module
  {
    public:
    AssetManager();
    ~AssetManager();

    void BroadcastMessage(Message* msg) {}

    template <typename T>
    T* NewAsset(std::string name, std::string path)
    {
      if (SDL_LockMutex(lock) == 0)
      {
        T* a = static_cast<T*>(assets.insert(std::make_pair(name, new T(name.c_str(), path.c_str()))).first->second);
        SDL_UnlockMutex(lock);

        return a;
      }
      else
        std::cout << "Couldn't lock mutex\n";

      return nullptr;
    }

    template <typename T>
    T* GetAsset(const char* name)
    {
      auto a = assets.find(name);
      return a != assets.end() ? static_cast<T*>(a->second) : nullptr ;
    }

    const std::string& GetBase() { return baseDir; }
    const std::string& GetAsset() { return assetDir; }
    const std::string& GetSource() { return sourceDir; }

    private:
      void GetExtensions();
      void LoadFiles();

      FileSystem* fileSys;

      std::string baseDir;
      std::string assetDir;
      std::string sourceDir;

      std::map<std::string, Asset*> assets;
      std::vector<const char*> extensions;

      SDL_mutex* lock;
  };

}

#endif