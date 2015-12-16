// Thanks to: http://www.piko3d.com/tutorials/libpng-tutorial-loading-png-files-from-streams

#include "pngloader.h"

#include <iostream>
#include <cstdio>

namespace System
{
  PNGLoader::PNGLoader(const char* path)
  {
    file = ::fopen(path, "rb");

    // Make sure we're actually reading a png.
    if (!Validate())
      std::cout << path << " isn't a valid png file!\n" << std::endl;

    Initialize();

    InterpretFile();

    RetrieveInfo();

    // For OpenGL, we have to reverse the image, as OpenGL wants it from bottom left, up
    SetupData();

    fclose(file);
  }

  PNGLoader::~PNGLoader()
  {
    png_destroy_read_struct(&pread, &pinf, NULL);
  }

  bool PNGLoader::Validate()
  {
    // Signature of a PNG is 8 bytes.
    unsigned char sig[sizeof(char) * 8];

    // Signature bytes are read in
    fread((char*)(sig), sizeof(char), 8, file);

    return !png_check_sig(sig, 8) ? false : true;
  }

  bool PNGLoader::Initialize()
  {
    // TODO: Careful, didn't implement our error handler callback yet...
    pread = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!pread)
      return false;

    pinf = png_create_info_struct(pread);
    
    if (!pinf)
    {
      png_destroy_read_struct(&pread, NULL, NULL);
      return false;
    }

    return true;
  }

  void PNGLoader::InterpretFile()
  {
    png_init_io(pread, file);
    png_set_sig_bytes(pread, 8);
    png_read_info(pread, pinf);
  }

  void PNGLoader::RetrieveInfo()
  {
    png_get_IHDR(pread, pinf, &imgWidth, &imgHeight, &bitDepth, &colorType, NULL, NULL, NULL);

    channels = png_get_channels(pread, pinf);

    switch(colorType)
    {
    case PNG_COLOR_TYPE_PALETTE:
      png_set_palette_to_rgb(pread);
      channels = 3;
      break;

      // Can set greyscale if need be
    }

    // If we have a transparency, make it full alpha channel.
    if (png_get_valid(pread, pinf, PNG_INFO_tRNS))
    {
      png_set_tRNS_to_alpha(pread);
      ++channels;
    }

    if (bitDepth == 16)
      png_set_strip_16(pread);
  }

  void PNGLoader::SetupData()
  {
    rowPtrs = new png_bytep[imgHeight];
    data = new char[imgWidth * imgHeight * bitDepth * channels / 8];
    const unsigned int stride = imgWidth * bitDepth * channels / 8;

    for (size_t i = 0; i < imgHeight; i++)
    {
      png_uint_32 q = (imgHeight- i - 1) * stride;

      rowPtrs[i] = (png_bytep)data + q;
    }

    png_read_image(pread, rowPtrs);
  }

  /*
  void PNGLoader::HandleError()
  {
    if (setjmp(png_jmpbuf(pread)))
    {
      png_destroy_read_struct(&pread, &pinf, NULL);
      if (rowPtrs)
        delete [] rowPtrs;

      if (data)
        delete [] data;

      std::cout << "Couldn't read the PNG file!\n";
    }
  }
  */
}