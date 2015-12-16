#ifndef PNGLOADER_H_
#define PNGLOADER_H_

#include "filesystem.h"
#include "..\\..\\frameworks\\libpng\\include\\libpng\\png.h"

#include <fstream>

namespace System
{
  struct PNGLoader
  {
    PNGLoader(const char* path);
    ~PNGLoader();

    png_uint_32 imgWidth, imgHeight;
    int bitDepth, channels, colorType;
    char* data;

  private:
    png_structp pread;
    png_infop pinf;
    png_bytep* rowPtrs;
    FILE* file;

    // Validate the first 8 bytes are infact for PNG.
    bool Validate();
    // Set up our png structs here.
    bool Initialize();
    // Read in data to info, read structs
    void InterpretFile();
    // Get info from image.
    void RetrieveInfo();
    // Setup our png data for use.
    void SetupData();

    // Handle error
    static png_error_ptr HandleError();
  };
}

#endif