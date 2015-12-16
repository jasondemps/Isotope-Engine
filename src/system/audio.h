#ifndef AUDIO_H
#define AUDIO_H

#include "FMOD\fmod.hpp"
#include "module.h"
#include "..\\resources\\assetmanager.h"
#include "..\\system\\messagehandle.h"

namespace System
{
  class Audio : public Module, public MessageHandle
  {
  public:
    Audio(AssetManager* assetManager);
    ~Audio();

    void Update();

    // Lua
    static int LoadSound(lua_State* l);
    static int LoadStream(lua_State* l);

    // Setters
    static int SetLoop(lua_State* l);
    static int SetVolume(lua_State* l);

    static int Play(lua_State* l);
    static int Stop(lua_State* l);

    void BroadcastMessage(Message* msg) {}

  private:
    AssetManager* assetManager;

    const int numChannels;
    FMOD::System* system;
    FMOD::Channel* streamChannel, *sfxChannel;
  };
}

#endif