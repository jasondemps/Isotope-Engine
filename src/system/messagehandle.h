#ifndef MESSAGEHANDLE_H_
#define MESSAGEHANDLE_H_

#include "message.h"

namespace System
{
  class MessageHandle
  {
  public:
    virtual ~MessageHandle() {}

    virtual void BroadcastMessage(Message* msg) = 0;
  };
}

#endif