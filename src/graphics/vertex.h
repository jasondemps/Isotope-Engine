#ifndef VERTEX_H_
#define VERTEX_H_

namespace Graphics
{
  struct Vertex
  {
    Vertex(float x = 0, float y = 0, float z = 0, float u = 0, float v = 0) : x(x), y(y), z(z), u(u), v(v) {}
    float x, y, z;
    float u, v;
  };
}

#endif