#include "DrawableFactory.h"
#include "sprite.h"
#include "..\\system\\modulehandler.h"
#include "graphicsmodule.h"

#include "window.h"

namespace Graphics
{
  DrawableFactory::DrawableFactory(System::AssetManager** assetManager) : totalObjects(drawables.size()), assetManager(*assetManager) {}

  DrawableFactory::~DrawableFactory() 
  {
    for (auto d : drawables)
      delete d;

    drawables.clear();
  }

  int DrawableFactory::NewSprite(lua_State* l)
  {
    DrawableFactory& drawFact = System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<GraphicsModule*>()->GetDrawFact();

    const char* texture = lua_tostring(l, -1);

    //drawFact.assetManager->GetAsset<System::ImageAsset>(texture);
    /*
    lua_pushstring(l, "count");
    lua_gettable(l, 2);

    int elem = lua_tointeger(l, -1);

    lua_Number *elems = new lua_Number[elem];

    for (int i = 1; i <= elem; ++i)
    {
      lua_gettable(l, i);

      // Should be 3 elements per vertex...
      lua_Number subElems[3];

      elems[i-1] = lua_tonumber(l, -1);
    }
    */

    // Create a new sprite with a unique ID, store it, then pass the ID back to Lua.
    Sprite* spr = new Sprite(++drawFact.totalObjects);//, drawFact.assetManager->GetAsset<System::ImageAsset>(texture));

    drawFact.drawables.push_back(spr);

    lua_pushinteger(l, drawFact.totalObjects);

    return 1;
  }

  std::vector<Drawable*> & DrawableFactory::GetDrawables() { return drawables; }
}