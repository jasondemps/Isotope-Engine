#include "keyboard.h"

#include <iostream>

namespace System
{
  Keyboard::Keyboard() : Module("keyboard", this), activeKey(nullptr), pressed(0)
  {
    evTypes[arrSize++] = SDL_KEYDOWN;
    evTypes[arrSize++] = SDL_KEYUP;

    // Expose keyboard checks to Lua
    AddEntry("KeyDown", &Keyboard::KeyDown);
    AddEntry("KeyPressed", &Keyboard::KeyPressed);
    AddEntry("KeyUp", &Keyboard::KeyUp);

    PushEntries();
  }

  Keyboard::~Keyboard() {}

  void Keyboard::PushEvent(SDL_Event & ev)
  {
    // This got called, so we should have an event to process!
    // Process the event based off the type.
    // Set the active key, so if Lua wants to inspect it, it can.
    for (auto e : evTypes)
      if (e == ev.type)
        activeKey = &ev.key;
  }

  void Keyboard::Update()
  {
    // Reset the pointer, so we won't sit on the current key forever.
    //activeKey = nullptr;
  }

  int Keyboard::KeyDown(lua_State* l)
  {
    const char* checkKey = lua_tostring(l, -1);

    Keyboard* kb = ModuleHandler::Get().GetModule("keyboard")->GetParentAs<Keyboard*>();

    if (kb->activeKey)
      // If the current key is a keydown event
      if (kb->activeKey->type == SDL_KEYDOWN)
        // If we get the key we're looking for.
        if (strcmp(checkKey, SDL_GetScancodeName(kb->activeKey->keysym.scancode)) == 0)
        {
          lua_pushboolean(l, 1);
          kb->activeKey = nullptr;

          return 1;
        }

    lua_pushboolean(l, 0);

    return 1;
  }

  int Keyboard::KeyPressed(lua_State* l)
  {
    const char* checkKey = lua_tostring(l, -1);

    Keyboard* kb = ModuleHandler::Get().GetModule("keyboard")->GetParentAs<Keyboard*>();

    if (kb->activeKey)
      // If the current key is a keydown event
      if (kb->activeKey->type == SDL_KEYDOWN && kb->pressed == 0)
        // If we get the key we're looking for.
        if (strcmp(checkKey, SDL_GetScancodeName(kb->activeKey->keysym.scancode)) == 0)
        {
          kb->pressed = 1;
          kb->activeKey = nullptr;
          lua_pushboolean(l, 1);

          return 1;
        }

    lua_pushboolean(l, 0);

    return 1;
  }

  int Keyboard::KeyUp(lua_State* l)
  {
    const char* checkKey = lua_tostring(l, -1);

    Keyboard* kb = ModuleHandler::Get().GetModule("keyboard")->GetParentAs<Keyboard*>();

    if (kb->activeKey)
    // If we get the key we're looking for.
      if (strcmp(checkKey, SDL_GetScancodeName(kb->activeKey->keysym.scancode)) == 0)
        // If the current key is a keydown event
        if (kb->activeKey->type == SDL_KEYUP)
        {
          // See if we can reset the pressed flag.
          if (kb->pressed)
            kb->pressed = 0;

          kb->activeKey = nullptr;

          lua_pushboolean(l, 1);
          return 1;
        }

    lua_pushboolean(l, 0);

    return 1;
  }
}