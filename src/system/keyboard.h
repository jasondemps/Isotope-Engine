#ifndef INPUT_H_
#define INPUT_H_

#include "module.h"
#include "eventlistener.h"

#include "SDL\\SDL.h"

namespace System
{
  class Keyboard : public Module, public EventListener
  {
  public:
    Keyboard();
    virtual ~Keyboard();

    void Update();
    void PushEvent(SDL_Event & ev);

    static int KeyDown(lua_State* l);
    static int KeyPressed(lua_State* l);
    static int KeyUp(lua_State* l);

  private:
    SDL_KeyboardEvent* activeKey;
    char pressed;
  };
}

#endif