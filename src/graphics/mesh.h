#ifndef MESH_H_
#define MESH_H_

#include "texture.h"
#include "renderable.h"
#include "glinit.h"
#include "vertex.h"

#include <vector>

namespace Graphics
{
  enum DrawMode {TRIANGLES, LINES};

  class Mesh : public Renderable
  {
  public:
    Mesh(DrawMode mode = TRIANGLES);
    Mesh(Texture const & tex);

    ~Mesh();

    // Give Vertices or Indices to the Mesh
    void NewVertex(float x_, float y_, float z_, float u_, float v_);
    void AddVertex(Vertex const & vert_);

    void AddLine(GLubyte f, GLubyte s);
    void AddTri(GLubyte f, GLubyte s, GLubyte t);

    void SetDrawMode(DrawMode mode);

    void Work();
    void Render();

  private:
    std::vector<GLubyte> mIndices;
    std::vector<Vertex> mVertices;
    GLuint mVertBuf, mIndBuf;
    DrawMode drawMode;
  };
}

#endif