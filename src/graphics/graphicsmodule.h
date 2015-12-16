#ifndef GRAPHICSMODULE_H_
#define GRAPHICSMODULE_H_

#include "window.h"
#include "DrawableFactory.h"
#include "technique.h"
#include "drawable.h"
#include "..\\system\\module.h"
#include "..\\log\\log.h"
#include "..\\resources\\assetmanager.h"
#include "..\\system\\messagehandle.h"
#include "..\\system\\message.h"

#include <map>
#include <unordered_map>
#include <vector>

// This is the frontend for all gfx things <-> lua

namespace Graphics
{
  class GraphicsModule : public System::Module, public System::MessageHandle
  {
  public:
    friend class DrawableFactory; // Using this as a test
    GraphicsModule(System::Log* logger, System::AssetManager* assetManager);
    ~GraphicsModule();

    // Functions to expose to Lua
    static int BindUniform(lua_State *l);

    static void Render();

    // Write some getters
    DrawableFactory& GetDrawFact();
    Window& GetWindow();
    inline Technique* GetCurrentTechnique() const { return currTechnique; }

    void BroadcastMessage(System::Message* msg) {}

  private:
    Technique* currTechnique;
    System::AssetManager* assetManager;
    System::Log* logger;
    Window window;
    DrawableFactory drawFactory;
    std::unordered_map<const char*, Technique*> techniques;
  };
}

#endif