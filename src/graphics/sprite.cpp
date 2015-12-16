#include "sprite.h"
#include "..\\system\\modulehandler.h"
#include <iostream>

namespace Graphics
{
  // Just testing
  Sprite::Sprite(int id_, System::ImageAsset* tex) : shape(50), body(shape, Math::Vec4(0,0,0))
  {
    visible = 1;
    id = id_;

    // Mesh stuff
    mesh = new Mesh();

    mesh->AddVertex(Vertex(-1, -1, -1));
    mesh->AddVertex(Vertex(1, -1, -1));
    mesh->AddVertex(Vertex(1, 1, -1));
    mesh->AddVertex(Vertex(-1, 1, -1));

    mesh->AddTri(0, 1, 2);
    mesh->AddTri(2, 3, 0);

    // Check for a texture
    if (tex)
    {
      //texture = new Texture(tex);
    }

    mesh->Send();
  }

  void Sprite::Finalize()
  {
    mesh->Send();
  }

  Sprite::~Sprite() 
  {
    delete mesh;
  }

  void Sprite::Render()
  {
    if (texture)
      texture->Render();

    if (mesh)
      mesh->Render();
  }
}