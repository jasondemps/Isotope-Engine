#ifndef TECHNIQUE_H_
#define TECHNIQUE_H_

#include "glinit.h"
#include "..\\resources\\assetmanager.h"
#include "renderable.h"

#include <string>

namespace Graphics
{
  class Technique : public Renderable
  {
  public:
    Technique(System::AssetManager& assetManager, const char* vertex, const char* frag);
    ~Technique();

    GLuint GetProgram() const;

    void Work();
    void Render();

  private:
    GLuint mProgramID;
    System::AssetManager& assetManager;

    // Shader stuff
    std::string mVertPath, mFragPath;
    std::string mVertContent, mFragContent;
    GLuint mShaderVertID, mShaderFragID;
  };
}

#endif