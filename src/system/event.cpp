#include "event.h"

namespace System
{
  void Event::AddListener(EventListener* l)
  {
    listenerObjects.push_back(l);

    // Insert all Events we are listening to.
    for (int i = 0; i < l->arrSize; ++i)
      eventListeners.insert(std::make_pair(l->evTypes[i], l));
  }
  /*
  void Event::RemoveListener(EventListener* l)
  {
    for (auto iter = listenerObjects.begin(); iter != listenerObjects.end(); ++iter)
      if (*iter == l)
        listenerObjects.erase(iter);

    /* Gotta remove all listener entries from the map. But this'll be mean...ill save it for later.
    auto foundListener = 

    eventListeners.erase(l);
    
  }*/

  void Event::Update()
  {
    // For each attached listener type, we should update them from here.
    // Or else we'll have to do it externally from somewhere else and could get nasty.
    //for (auto el : listenerObjects)
    //  el->Update();

    // Look for some events!
    //while (SDL_PollEvent(&ev))
    if (SDL_PollEvent(&ev))
    {
      // Get all listeners that are looking for our event type
      auto foundListeners = eventListeners.equal_range(ev.type);

      // Send our event to each of'em
      for (auto el = foundListeners.first; el != foundListeners.second; ++el)
        el->second->PushEvent(ev);
    }
  }
}