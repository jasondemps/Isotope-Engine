#ifndef IMAGE_H_
#define IMAGE_H_

#include "..\..\frameworks\zlib\include\zlib\zlib.h"
//#include "..\\..\\frameworks\\libpng\\include\\libpng\\png.h"

struct Image
{
  int width, height, channels;
  const unsigned char* data;
};

#endif