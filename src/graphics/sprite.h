#ifndef SPRITE_H_
#define SPRITE_H_

#include "drawable.h"
#include "..\\system\\module.h"
#include "..\\math\\matrix4.h"
#include "..\\Physics\\PhysicsBody.h"
#include "..\\Physics\\Circle.h"

// Fowrad decl.
struct System::ImageAsset;
class DrawableFactory;

namespace Graphics
{
  class Sprite : public Drawable
  {
  public:
    friend class DrawableFactory;
    Sprite(int id_, System::ImageAsset* tex = nullptr);
    virtual ~Sprite();

    void Finalize();

    void Render();

  private:
    Physics::Circle shape;
    Physics::PhysicsBody body;
    Mesh* mesh;
    Texture* texture;
  };
}

#endif