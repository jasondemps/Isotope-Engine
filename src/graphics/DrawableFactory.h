#ifndef DRAWABLEFACTORY_H_
#define DRAWABLEFACTORY_H_

#include "drawable.h"
#include "..\\system\\module.h"
#include "..\\resources\\assetmanager.h"

#include <vector>

namespace Graphics
{
  class DrawableFactory
  {
  public:
    DrawableFactory(System::AssetManager** assetManager);
    ~DrawableFactory();

    // Factory Methods
    static int NewSprite(lua_State* l);

    std::vector<Drawable*> & GetDrawables();

  private:
    int totalObjects;
    std::vector<Drawable*> drawables;
    System::AssetManager* assetManager;
  };
}

#endif