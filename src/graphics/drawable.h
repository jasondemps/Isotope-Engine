#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "renderable.h"
#include "mesh.h"
#include "texture.h"

namespace Graphics
{
  class Drawable
  {
  public:
    virtual ~Drawable() { }

    void SetVisible(int v) { visible = v; }
    inline int GetVisible() const { return visible; }

    inline int GetID() const { return id; }

    virtual void Render() = 0;
    
  protected:
    int visible;
    int id;
  };
}

#endif