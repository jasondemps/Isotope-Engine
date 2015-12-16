#include "mesh.h"

#include <iostream>

namespace Graphics
{
  Mesh::Mesh(DrawMode mode) : drawMode(mode)
  {
  }

  Mesh::Mesh(Texture const & tex)
  {
  }

  Mesh::~Mesh()
  {
    // This will need to be fixed
    gl::DeleteBuffers(1, &mIndBuf);
    gl::DeleteBuffers(1, &mVertBuf);
  }

  void Mesh::SetDrawMode(DrawMode mode)
  {
    drawMode = mode;
  }

  void Mesh::Work()
  {
    // Gen buffers
    gl::GenBuffers(1, &mVertBuf);
    gl::GenBuffers(1, &mIndBuf);

    gl::EnableVertexAttribArray(0);
    // Should be texture attrib
    gl::EnableVertexAttribArray(1);

    gl::BindBuffer(gl::ARRAY_BUFFER, mVertBuf);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, mIndBuf);


    // Use our attrib ptr
    gl::VertexAttribPointer(
      0,              // attribute #
      3,              // size 
      gl::FLOAT,      // type
      gl::FALSE_,     // normalized
      sizeof(Vertex), // stride
      NULL            // buffer offset
      );

    gl::VertexAttribPointer(
      1,              // attribute #
      2,              // size 
      gl::FLOAT,      // type
      gl::FALSE_,     // normalized
      sizeof(Vertex), // stride
      (const void*)(sizeof(float) * 3)            // buffer offset
      );
      
    // VBO
    gl::BindBuffer(gl::ARRAY_BUFFER, mVertBuf);
    gl::BufferData(gl::ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), mVertices.data(), gl::STATIC_DRAW);
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);

    // IBO
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, mIndBuf);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(mIndices[0]), mIndices.data(), gl::STATIC_DRAW);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);
  }

  void Mesh::Render()
  {
    gl::BindBuffer(gl::ARRAY_BUFFER, mVertBuf);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, mIndBuf);

    // Use our attrib ptr
    gl::VertexAttribPointer(
      0,              // attribute #
      3,              // size 
      gl::FLOAT,      // type
      gl::FALSE_,     // normalized
      sizeof(Vertex), // stride
      NULL            // buffer offset
      );
    
    gl::VertexAttribPointer(
      1,              // attribute #
      2,              // size 
      gl::FLOAT,      // type
      gl::FALSE_,     // normalized
      sizeof(Vertex), // stride
      (const void*)(sizeof(float) * 3)            // buffer offset
      );
      

    // Draw here....
    gl::DrawElements(drawMode == TRIANGLES ? gl::TRIANGLES : gl::LINE_LOOP, mIndices.size(), gl::UNSIGNED_BYTE, 0);

    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
  }

  void Mesh::NewVertex(float x_, float y_, float z_, float u_, float v_)
  {
    mVertices.emplace_back(x_, y_, z_, u_, v_);
  }

  void Mesh::AddVertex(Vertex const & vert_)
  {
    mVertices.push_back(vert_);
  }

  void Mesh::AddLine(GLubyte f, GLubyte s)
  {
    mIndices.push_back(f); mIndices.push_back(s);
  }

  void Mesh::AddTri(GLubyte f, GLubyte s, GLubyte t)
  {
    mIndices.push_back(f); mIndices.push_back(s); mIndices.push_back(t);
  }
}