#include "renderable.h"

#include "graphicsmodule.h"
#include "..\\system\\modulehandler.h"
#include "window.h"

namespace Graphics
{
  Renderable::Renderable() : canRender(false)
  {
  }

  Renderable::~Renderable()
  {
  }

  void Renderable::Send()
  {
    Window* mainWin = &System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<GraphicsModule*>()->GetWindow();

    if (mainWin)
    {
      SDL_mutexP(mainWin->renderMutex);
        mainWin->renderQueue.push(this);
      SDL_mutexV(mainWin->renderMutex);
    }
  }
}