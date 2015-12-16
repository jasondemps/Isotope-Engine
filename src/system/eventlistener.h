#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

#include "SDL\\SDL.h"

#include <array>

namespace System
{
  const int EVENTTYPES = 16;

  class EventListener
  {
  public:
    EventListener() : arrSize(0) {}
    virtual ~EventListener() {}
    
    virtual void PushEvent(SDL_Event & ev) = 0;
    //virtual void Update() = 0;

    std::array<Uint32, EVENTTYPES> evTypes;
    int arrSize;
  };
}

#endif