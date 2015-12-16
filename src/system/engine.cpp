#include "engine.h"

#include <iostream>

namespace System
{
  Engine::Engine() : Module("engine", this)
  {
    moduleHandler = new ModuleHandler();
    assetManager = new AssetManager();
    
    moduleHandler->Initialize(assetManager);
    
    log = new Log();
    ev = new Event();
    audio = new Audio(assetManager);

    RegisterSystem(assetManager);
    RegisterSystem(moduleHandler);
    RegisterSystem(log);
    RegisterSystem(new Graphics::GraphicsModule(log, assetManager));
    RegisterSystem(new Audio(assetManager));
    RegisterSystem(ev);

    // Add listeners
    ev->AddListener(keyboard = new Keyboard());

    AddEntry("Update", &Engine::SubSystemProcess);
    AddEntry("GetTicks", &Engine::GetTicks);

    PushEntries();

    // Just using this so i can test stuff!
    log->DumpGameTable();
  }

  Engine::~Engine() 
  {
    for (auto& s : systems)
      delete s;

    systems.clear();

    delete keyboard;
  }

  int Engine::GetTicks(lua_State* l)
  {
    lua_pushnumber(l, SDL_GetTicks());

    return 1;
  }

  int Engine::SubSystemProcess(lua_State* l)
  {
    // Any system update stuff should be done here.
    Engine* engine = ModuleHandler::Get().GetModule("engine")->GetParentAs<Engine*>();

    // Pump Events
    engine->ev->Update();

    // Update audio system
    engine->audio->Update();

    // TODO:
    // We might get a return value from each sub system, so we can pass it on to Lua and force it out of its loop.

    return 0;
  }

  void Engine::RegisterSystem(MessageHandle* sys)
  {
    systems.push_back(sys);
  }

  void Engine::RemoveSystem(MessageHandle* sys)
  {
    // Try to remove the system.
    for (auto s = systems.begin(); s != systems.end(); ++s)
      if (sys == *s)
        systems.erase(s);
  }

  int Engine::Update()
  {
    // Should setup everything else before we execute our main lua entry
    // It's good form, but isn't 100% required....maybe......
    //int returnCode = 1;

    // Game Loop. 
    // Let's control it with scripting!
    //while ((returnCode = moduleHandler.ExecuteScriptMain()) > 0) ;
    /*{
        // Pump Events
      event.Update();

      // Update audio system
      audio.updateSound();
    }
    */
    //return returnCode;
    return moduleHandler->ExecuteScriptMain();
  }
}