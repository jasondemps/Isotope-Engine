#include "gamepad.h"

namespace System
{
  Gamepad::Gamepad() : Module("gamepad", this)
  {
    //controllers.fill(nullptr);

    // Joystick events
    /*
    evTypes[arrSize++] = SDL_JOYAXISMOTION;
    evTypes[arrSize++] = SDL_JOYHATMOTION;
    evTypes[arrSize++] = SDL_JOYBUTTONDOWN;
    evTypes[arrSize++] = SDL_JOYBUTTONUP;
    evTypes[arrSize++] = SDL_JOYDEVICEADDED;
    evTypes[arrSize++] = SDL_JOYDEVICEREMOVED;
    */
    // Controller events
    evTypes[arrSize++] = SDL_CONTROLLERAXISMOTION;
    evTypes[arrSize++] = SDL_CONTROLLERBUTTONDOWN;
    evTypes[arrSize++] = SDL_CONTROLLERBUTTONUP;
    evTypes[arrSize++] = SDL_CONTROLLERDEVICEADDED;
    evTypes[arrSize++] = SDL_CONTROLLERDEVICEREMOVED;
    evTypes[arrSize++] = SDL_CONTROLLERDEVICEREMAPPED;

    /*
    Entry* lol[4] = {
      new EntryBoolean("Pad1", false),
      new EntryBoolean("Pad2", false),
      new EntryBoolean("Pad3", false),
      new EntryBoolean("Pad4", false)
    };

    AddEntry("Pads", std::vector<Entry*>(lol, lol + sizeof(lol) / sizeof(Entry*)));
    */
  }

  Gamepad::~Gamepad() {}

  void Gamepad::PushEvent(SDL_Event & ev)
  {
    /*
    for (auto e : evTypes)
      // Make sure we get a type of event we're looking for
      switch (e == ev.type)
      {
        // See if its an axis motion
      case SDL_CONTROLLERAXISMOTION:
        std::cout << "Controller: Axis Motion\n";
        // Look for the controller ID to apply the axis motion to.
        //for (SDL_GameController& c : controllers)
        //  c.

        //controllers.at(ev.cdevice.which). = ev.caxis;
        break;
      }
      */
  }

  void Gamepad::Update()
  {
  }
}