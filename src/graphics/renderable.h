#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "glinit.h"

int Thread_ProcessContext(void* data);

namespace Graphics
{
  class GraphicsModule;

  class Renderable
  {
  public:
    friend int ::Thread_ProcessContext(void* data);
    friend class GraphicsModule;

    Renderable();
    virtual ~Renderable();

    void Send();

    virtual void Work() = 0;
    virtual void Render() = 0;

  protected:
    bool canRender;
  };
}

#endif