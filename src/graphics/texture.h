#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "renderable.h"
#include "Image.h"
#include "technique.h"

#include <vector>

struct System::ImageAsset;

namespace Graphics
{
  class Texture : public Renderable
  {
  public:
    Texture(System::ImageAsset* image);
    // Use this to pass in an image to be built...essentially
    //Texture(int width, int height, const unsigned char* pixelArray);
    ~Texture();

    void Load(const char* name, int width, int height);

    void AddUV(GLfloat u, GLfloat v);

    void Work();
    void Render();

  private:
    Technique* currTech;
    GLuint uvBufferID, textureID;
    std::vector<GLfloat> uvBufferData;
    System::ImageAsset* image;
  };
}

#endif