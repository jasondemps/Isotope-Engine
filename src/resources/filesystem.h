#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

//#include "TinyDir\\tinydir.h"

#include <utility>
#include <list>
#include <string>

namespace System
{
  enum EnumType {ALL, FILES, DIRECTORIES};

  class FileSystem
  {
  public:
    FileSystem(std::string& path);
    ~FileSystem();

    // Directory Traversal
    int Next();
    int Prev();

    //const char* CurrentDir() const { return dir.path; }
    const std::list<std::pair<const char*, const char*>>& Enumerate(EnumType type = ALL);

    static std::string GetExtension(std::string& path)
    {
      std::string::size_type pos = path.rfind('.');

      return pos == path.npos ? std::string() : path.substr(pos) ;
    }

  private:
    std::list<std::pair<const char*, const char*>> dirList;
    std::string base, currDir;
    //tinydir_dir dir;
  };
}

#endif