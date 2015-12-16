#ifndef ENGINE_H_
#define ENGINE_H_

#include "messagehandle.h"
#include "module.h"

#include "modulehandler.h"
#include "..\\resources\\assetmanager.h"
#include "..\\log\\log.h"
#include "..\\graphics\\graphicsmodule.h"
#include "event.h"
#include "keyboard.h"
#include "audio.h"

#include <string>

namespace System
{
  class Engine : public Module, public MessageHandle
  {
  public:
    Engine();
    ~Engine();

    int Update();

    static int GetTicks(lua_State* l);
    static int SubSystemProcess(lua_State* l);

    void BroadcastMessage(Message* msg) {}

  private:
    void RegisterSystem(MessageHandle* sys);
    void RemoveSystem(MessageHandle* sys);

    AssetManager* assetManager;
    Log* log;
    Event* ev;
    Audio* audio;
    ModuleHandler* moduleHandler;
    /*
    AssetManager assetManager;
    ModuleHandler moduleHandler;
    Log log;
    Graphics::GraphicsModule graphicsModule;
    Audio audio;
    Event event;
    Keyboard* keyboard;
    */
    std::vector<MessageHandle*> systems;
    Keyboard* keyboard;
    bool isRunning;
  };
}

#endif