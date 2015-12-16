#include "engine.h"

#include <iostream>

int main(int argc, char** argv)
{
  System::Engine engine;

  if (engine.Update() != 0)
  {
    std::cout << "Execution Halted.\n" << std::endl;
    return -1;
  }

  return 0;
}