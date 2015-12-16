#ifndef WINDOW_H_
#define WINDOW_H_

#include "..\\log\\log.h"
#include "glinit.h"
#include "SDL\\SDL.h"
#include "..\\system\\module.h"
#include "..\\system\\event.h"
#include "..\\system\\eventlistener.h"
#include "DrawableFactory.h"

#include <queue>

int Thread_ProcessContext(void* data);

namespace Graphics
{
  // Foward Declarations
  class Renderable;

  class Window : public System::Module, System::EventListener
  {
  public:
    friend class DrawableFactory;
    friend class Renderable;
    friend int ::Thread_ProcessContext(void* data);

    Window(System::Log& logger_);
    ~Window();

    void (*Render)();

    void PushEvent(SDL_Event & ev);

  private:
    int Initialize();

    System::Log& logger;

    // Event handler
    System::Event event;

    // Graphics stuffs
    SDL_Thread* renderThread;
    SDL_mutex* renderMutex;
    SDL_Window* window;
    SDL_GLContext context;

    GLuint vertArray;

    std::queue<Renderable*> renderQueue;

    bool valid, legacy;
  };
}

#endif