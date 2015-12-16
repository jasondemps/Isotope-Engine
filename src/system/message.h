#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MsgType
{
  Collision
};

namespace System
{
  struct Message
  {
    Message(MsgType type) : type(type) {}
    virtual ~Message() {}
    MsgType type;
  };
}

#endif