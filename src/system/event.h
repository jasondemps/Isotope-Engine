#ifndef EVENT_H_
#define EVENT_H_

#include "SDL\\SDL.h"
#include "eventlistener.h"
#include "..\\system\\messagehandle.h"

#include <map>
#include <vector>

namespace System
{
  struct Event : public MessageHandle
  {
  public:
    /*
    Event();
    ~Event();
    */
    void AddListener(EventListener* l);
    //void RemoveListener(EventListener* l);

    void Update();

    void BroadcastMessage(Message* msg) {}

  private:
    std::vector<EventListener*> listenerObjects;
    std::map<Uint32, EventListener*> eventListeners;
    SDL_Event ev;
  };
}

#endif