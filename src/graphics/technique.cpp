#include "technique.h"

namespace Graphics
{
  Technique::Technique(System::AssetManager& assetManager, const char* vertex, const char* frag) : assetManager(assetManager), mVertPath(vertex), mFragPath(frag)
  {
  }

  void Technique::Work()
  {
    char error[256];
    mProgramID = gl::CreateProgram();
    mShaderFragID = gl::CreateShader(gl::FRAGMENT_SHADER);
    mShaderVertID = gl::CreateShader(gl::VERTEX_SHADER);

    auto v = assetManager.NewAsset<System::FileAsset>(mVertPath + ".vert", assetManager.GetBase() + "src\\graphics\\shaders\\" + mVertPath + ".vert");
    auto f = assetManager.NewAsset<System::FileAsset>(mFragPath + ".frag", assetManager.GetBase() + "src\\graphics\\shaders\\" + mFragPath + ".frag");

    // Send shaders to gfx card
    const GLchar* info = v->data.c_str();
    GLint length = v->data.length();

    gl::ShaderSource(mShaderVertID, 1, &info, &length);

    info = f->data.c_str();
    length = f->data.length();

    gl::ShaderSource(mShaderFragID, 1, &info, &length);


    // Compile the shaders
    gl::CompileShader(mShaderVertID);

    gl::GetShaderInfoLog(mShaderVertID, 256, NULL, error);
    std::cout << error;

    gl::CompileShader(mShaderFragID);

    gl::GetShaderInfoLog(mShaderFragID, 256, NULL, error);
    std::cout << error;
    
    // Attach + Link Shaders
    gl::AttachShader(mProgramID, mShaderVertID);
    gl::AttachShader(mProgramID, mShaderFragID);

    gl::LinkProgram(mProgramID);
  }

  void Technique::Render()
  {
    if (canRender)
      gl::UseProgram(mProgramID);
  }

  GLuint Technique::GetProgram() const { return mProgramID; }

  Technique::~Technique()
  {
    gl::DetachShader(mProgramID, mShaderVertID);
    gl::DetachShader(mProgramID, mShaderFragID);

    gl::DeleteShader(mShaderVertID);
    gl::DeleteShader(mShaderFragID);

    gl::DeleteProgram(mProgramID);
  }
}