#include "texture.h"
#include "..\\system\\modulehandler.h"
#include "graphicsmodule.h"

#include "..\\resources\\assetmanager.h"

namespace Graphics
{
  Texture::Texture(System::ImageAsset* image) : image(image)
  {
    // Generate the texture
    gl::GenTextures(1, &textureID);
    gl::BindTexture(gl::TEXTURE_2D, textureID);

    // Setup basic stuff
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);

    // Read our data
    gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, image->pngData->imgWidth, image->pngData->imgWidth, 0, gl::RGBA, gl::UNSIGNED_BYTE, image->pngData->data);

    // Generate the UV buffer
    gl::GenBuffers(1, &uvBufferID);
    gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferID);
    gl::BufferData(gl::ARRAY_BUFFER, uvBufferData.size() * sizeof(uvBufferData[0]), uvBufferData.data(), gl::STATIC_DRAW);

    // Bind to the current uniform
    currTech = System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<GraphicsModule*>()->GetCurrentTechnique();

    //gl::GenSamplers(1, &

    // Not done!
    gl::GetUniformLocation(currTech->GetProgram(), "texSampler0");
    //gl::Uniform2i(currTech->GetProgram(), *elems);
  }

  Texture::~Texture()
  {
    gl::DeleteBuffers(1, &uvBufferID);
    gl::DeleteTextures(1, &textureID);
  }

  void Texture::AddUV(GLfloat u, GLfloat v)
  {
    uvBufferData.push_back(u); uvBufferData.push_back(v);
  }

  void Texture::Work()
  {
    gl::EnableVertexAttribArray(1);
    gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferID);

    gl::VertexAttribPointer(
      1,              // attribute #
      2,              // size 
      gl::FLOAT,      // type
      gl::FALSE_,     // normalized
      sizeof(Vertex), // stride
      (const void*)(sizeof(float) * 3)            // buffer offset
    );
  }

  void Texture::Render()
  {
    gl::BindTexture(gl::TEXTURE_2D, textureID);
  }
}