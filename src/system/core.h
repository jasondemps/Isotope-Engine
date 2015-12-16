#ifndef CORE_H_
#define CORE_H_

#include "module.h"

namespace System
{
  // Forward Declarations
  struct Log;

  class Core : public Module
  {
    public:
      Core(Log& logger_);
      ~Core();

      static int printnum(lua_State* l);
      static int Update(lua_State *l);

  private:
    Log& logger;
  };
}

#endif