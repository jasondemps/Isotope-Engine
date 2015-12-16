#include "window.h"
#include "renderable.h"
#include "..\\system\\modulehandler.h"
#include "graphicsmodule.h"

#include <iostream>

int Thread_ProcessContext(void* data)
{
  Graphics::Window* currWindow = static_cast<Graphics::Window*>(data);

  currWindow->context = SDL_GL_CreateContext(currWindow->window);

  SDL_GL_MakeCurrent(currWindow->window, currWindow->context);

  // Load neccessary OpenGL functions.
  #ifdef _WIN32
    if (!wgl::sys::LoadFunctions(wglGetCurrentDC()))
    {
      std::cout << "Window: Couldn't create WGL Context" << std::endl;
      return -1;
    }
  #else
      glx::sys::LoadFunctions();
  #endif

  // Init GL Functions
  // Once per program me thinks
  if (!gl::sys::LoadFunctions())
    std::cout << "Window: Didn't Load OpenGL! You're about to get pewp'd on!\n" << std::endl;

  // Init some GL flags
  gl::Enable(gl::BLEND);
  gl::Enable(gl::MULTISAMPLE);

  gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

  // Generate a VAO
  gl::GenVertexArrays(1, &currWindow->vertArray);

  // Send our technique to get processed
  System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<Graphics::GraphicsModule*>()->GetCurrentTechnique()->Send();

  // Render goes hurr
  while (currWindow->valid)
  {
    SDL_mutexP(currWindow->renderMutex);

      gl::ClearColor(0, 0, 0, 0);
      gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT | gl::STENCIL_BUFFER_BIT);

      gl::BindVertexArray(currWindow->vertArray);

      while (currWindow->renderQueue.size())
      {
        Graphics::Renderable* renderable = currWindow->renderQueue.front();

        currWindow->renderQueue.pop();

        renderable->Work();

        renderable->canRender = true;
      }

      // Draw dem thangs
      if (currWindow->Render)
        currWindow->Render();

      SDL_GL_SwapWindow(currWindow->window);

      gl::BindVertexArray(0);

    SDL_mutexV(currWindow->renderMutex);

    // Wait a tick....zing.
    int storedTicks = SDL_GetTicks();
    while (SDL_GetTicks() - storedTicks < 2);
  }

  return 0;
}

namespace Graphics
{
  Window::Window(System::Log& logger_) : System::Module("graphics", this), Render(nullptr), logger(logger_), event(System::Event()), valid(false), legacy(false)
  {
    if (Initialize() != 0) // If the window + context was created successfully
      std::cout << "Window: There were errors in initialization. This won't work." << std::endl;
  }

  void Window::PushEvent(SDL_Event & ev)
  {
    for (auto e : evTypes)
      switch(e)
      {
      case SDL_WINDOWEVENT_CLOSE:
        // Should try to close thangz.
        break;
      }
      /*
      if (e == ev.type)
        activeKey = &ev.window;
        */
  }

  int Window::Initialize()
  {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
      std::cout << "Couldn't initialize SDL!\n";

    // Try to initialize a 3.3 context, if we can't, fall back to 3.1 legacy.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) != 0)
    {
      std::cout << "Window: Couldn't init a 3.3 context! Trying a legacy 3.1" << SDL_GetError() << std::endl;

      if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) != 0)
      {
        std::cout << "Window: Uh...make sure your GFX card is plugged in...couldn't init a legacy context." << std::endl;
        return -1;
      }
      else
      {
        legacy = true;
        std::cout << "Window: Falling back to legacy. " << std::endl;
      }
    }

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1) ;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create the window
    window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

    // Show the window
    SDL_ShowWindow(window);

    // Set a boolean for the game's actual state.
    // Needed so the thread can exit someday.
    valid = true;

    renderMutex = SDL_CreateMutex();

    SDL_GL_MakeCurrent(window, nullptr);

    // Init OpenGL on its own thread. OpenGL will be on its own thread at all times.
    renderThread = SDL_CreateThread(Thread_ProcessContext, "Context", this);

    return 0;
  }

  Window::~Window()
  {
    SDL_WaitThread(renderThread, nullptr);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
  }
}