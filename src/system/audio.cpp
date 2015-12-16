#include "audio.h"
#include "modulehandler.h"
#include "..\\resources\\assetmanager.h"

namespace System
{
  Audio::Audio(AssetManager* assetManager) : assetManager(assetManager), numChannels(10), Module("audio", this)
  {
    System_Create(&system);
    system->init(numChannels, FMOD_INIT_NORMAL, 0);

    AddEntry("LoadSound", Audio::LoadSound);
    AddEntry("LoadStream", Audio::LoadStream);

    AddEntry("SetLoop", Audio::SetLoop);
    AddEntry("SetVolume", Audio::SetVolume);

    AddEntry("Play", Audio::Play);

    PushEntries();
  }

  Audio::~Audio()
  {
    system->close();
  }

  void Audio::Update()
  {
    system->update();
  }

  int Audio::LoadSound(lua_State* l)
  {
    // Point back to ourselves
    Audio* audio = System::ModuleHandler::Get().GetModule("audio")->GetParentAs<Audio*>();

    // Get file string from stack and Append the base directory + assets folder.
    std::string name = lua_tostring(l, 1);
    std::string path(audio->assetManager->GetAsset() + "sfx\\" + name + ".wav");

    // Cache the new asset
    AudioAsset* asset = audio->assetManager->NewAsset<AudioAsset>(name, path);

    // Make this asset a sound!
    asset->audioType = AudioAsset::SOUND;
    audio->system->createSound(asset->data.c_str(), FMOD_OPENMEMORY | FMOD_HARDWARE, &asset->exinfo, &asset->soundData);
    asset->soundData->setMode(FMOD_LOOP_OFF);

    // Set volume if it was passed
    if (lua_isnumber(l, 2))
      asset->volume = lua_tonumber(l, 2);

    // Send the new asset to Lua
    lua_pushlightuserdata(l, asset);

    return 1;
  }

  int Audio::LoadStream(lua_State* l)
  {
    // Point back to ourselves
    Audio* audio = System::ModuleHandler::Get().GetModule("audio")->GetParentAs<Audio*>();

    // Get file string from stack and Append the base directory + assets folder.
    std::string name = lua_tostring(l, 1);
    std::string path(audio->assetManager->GetAsset() + "bgm\\" + name + ".mp3");

    // Cache the new asset
    AudioAsset* asset = audio->assetManager->NewAsset<AudioAsset>(name, path);

    // Make this asset a stream!
    asset->audioType = AudioAsset::STREAM;
    audio->system->createStream(
      asset->data.c_str(),
      FMOD_HARDWARE | FMOD_OPENMEMORY,
      &asset->exinfo,
      &asset->soundData
      );
    asset->soundData->setMode(FMOD_LOOP_NORMAL);

    // Set volume if it was passed
    if (lua_isnumber(l, 2))
      asset->volume = lua_tonumber(l, 2);

    // Send the new asset to Lua
    lua_pushlightuserdata(l, asset);

    return 1;
  }

  int Audio::SetLoop(lua_State* l)
  {
    // Point back to ourselves
    Audio* audio = System::ModuleHandler::Get().GetModule("audio")->GetParentAs<Audio*>();

    // Get our pointer from the lua stack.
    AudioAsset* asset = static_cast<AudioAsset*>(lua_touserdata(l, 1));

    asset->soundData->setMode(lua_toboolean(l, 2) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

    return 0;
  }

  int Audio::SetVolume(lua_State* l)
  {
    // Point back to ourselves
    Audio* audio = System::ModuleHandler::Get().GetModule("audio")->GetParentAs<Audio*>();

    // Get our pointer from the lua stack.
    AudioAsset* asset = static_cast<AudioAsset*>(lua_touserdata(l, 1));

    // Get the value from the stack.
    asset->volume = luaL_checknumber(l, -2);

    return 0;
  }

  int Audio::Play(lua_State* l)
  {
    // Point back to ourselves
    Audio* audio = System::ModuleHandler::Get().GetModule("audio")->GetParentAs<Audio*>();

    // Get our pointer from the lua stack.
    AudioAsset* asset = static_cast<AudioAsset*>(lua_touserdata(l, 1));

    switch(asset->audioType)
    {
    case AudioAsset::SOUND:
      // Make sure we set the volume.
      if (asset->volume > 0)
      {
        audio->sfxChannel->setVolume(asset->volume);
        audio->system->playSound(FMOD_CHANNEL_FREE, asset->soundData, false, &audio->sfxChannel);
      }
      break;

    case AudioAsset::STREAM:
      if (asset->volume > 0)
      {
        audio->streamChannel->setVolume(asset->volume);
        audio->system->playSound(FMOD_CHANNEL_FREE, asset->soundData, false, &audio->streamChannel);
      }
      break;
    }

    return 0;
  }
}
