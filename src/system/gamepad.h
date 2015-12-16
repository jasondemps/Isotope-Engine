#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include "module.h"
#include "eventlistener.h"

#include <array>

namespace System
{
  class Gamepad : public Module, public EventListener
  {
  public:
    Gamepad();
    virtual ~Gamepad();

    void PushEvent(SDL_Event & ev);
    void Update();



  private:
    //std::array<SDL_GameController, 4> controllers;
    //std::vector<Entry*> controllers;
    SDL_ControllerAxisEvent* axisEvent;
  };
}

#endif