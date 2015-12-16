#ifndef GRAPHICSINIT_H_
#define GRAPHICSINIT_H_

#ifdef _WIN32
  #include "reqs\wgl\wgl_core_3_3.hpp"
#else
  #include "reqs\glx\glx_core_3_3.hpp"
#endif

#include "reqs\gl_core_3_3.hpp"

#endif