#include "core.h"
#include "modulehandler.h"
#include "..\resources\resourcemanager.h"

#include <iostream>

namespace System
{
  Core::Core(Log& logger_) : Module("core", this), logger(logger_)
  {
    // Initialize Scripting

    AddEntry("testNum", 5.0);
    AddEntry("teststringk", "LOLOLOLOLOL");
    // Vector is read sequentially
    //std::vector<Entry*> mEntries;
    //mEntries.push_back(new EntryString("teststring111", "datvalue"));
    //AddEntry("testTable", mEntries);

    // Test a function! :D
    AddEntry("Update", Core::Update);
    //lua_pushcfunction(ModuleHandler::Get().GetState(), &Core::printnum);
    AddEntry("printnum", Core::printnum);
    PushEntries();
    
    // Initialize Audio
    
    // Testing resources
    // Generic File
    /*
    Resource<File> testfile = ResourceManager::Get().NewResource<File>("test", "test.txt");
    std::cout << testfile() << std::endl;

    // Directories
    Resource<Directory> testDir = ResourceManager::Get().NewResource<Directory>("scripts", "../../src/scripts/");
    std::cout << testDir() << std::endl;
    */
  }

  int Core::printnum(lua_State* l)
  {
    std::cout << "Printnum got called!\n";
    return 0;
  }
  
  int Core::Update(lua_State *l)
  {

    return 0;
  }

  Core::~Core()
  {
  }
}