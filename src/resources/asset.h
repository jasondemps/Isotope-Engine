#ifndef ASSET_H_
#define ASSET_H_

#include <string>
#include <fstream>
#include <iostream>

#include "pngloader.h"
#include "filesystem.h"
#include "FMOD\\fmod.hpp"

namespace System
{
  struct Asset
  {
    Asset(const char* name, const char* path) : name(name), path(path) {}
    virtual ~Asset() {}
  
    const char* name, *path;
    std::string data;
  };

  struct FileAsset : public Asset
  {
    FileAsset(const char* name_, const char* path) : Asset(name, path) 
    {
      std::ifstream externFile(path);

      if (externFile.good())
      {
        // Seek to the end of the file, and resize the string to its reported size
        externFile.seekg(0, std::ios::end);
        data.resize((int) externFile.tellg());

        // Seek back to the beginning of the file and read the contents
        externFile.seekg(0, std::ios::beg);
        externFile.read(&data[0], data.length());
      }
      else
        std::cout << "File: Couldn't load file: " << path << std::endl;
    }

    virtual ~FileAsset() {}

  };

  struct DirAsset : public Asset
  {
    DirAsset(const char* name, const char* path) : Asset(name, path) { data = path; }
    virtual ~DirAsset() {}

  };

  struct AudioAsset : public Asset
  {
    enum AudioType { SOUND, STREAM };
    AudioAsset(const char* name, const char* path) : Asset(name, path), volume(1.f)
    {
      // Initialize exinfo
      memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
      exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);

      std::ifstream externFile(path, std::ios::binary);

      if (externFile.good())
      {
        // Seek to the end of the file, and resize the string to its reported size
        externFile.seekg(0, std::ios::end);
        data.resize(exinfo.length = (int) externFile.tellg());

        // Seek back to the beginning of the file and read the contents
        externFile.seekg(0, std::ios::beg);
        externFile.read(&data[0], data.length());
      }
      else
        std::cout << "AudioFile: Couldn't load AudioFile: " << path << std::endl;
    }

    virtual ~AudioAsset() {}

    float volume;
    FMOD_CREATESOUNDEXINFO exinfo;
    FMOD::Sound* soundData;
    AudioType audioType;
  };

  struct ImageAsset : public Asset
  {
    ImageAsset(const char* name, const char* path) : Asset(name, path)
    {
      std::ifstream imgFile(path, std::ios::binary);

      std::string ext(FileSystem::GetExtension(std::string(path)));

      pngData = new PNGLoader(path);
    }

    virtual ~ImageAsset() { delete pngData; }

    PNGLoader* pngData;
  };
}

#endif