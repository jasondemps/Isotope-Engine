#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Calculate ModelView based off Mesh + Camera
uniform mat4 Mesh;
uniform mat4 Camera;

// Projection
uniform mat4 Projection;

// Setup color shit

out vec2 UV;

void main()
{
  mat4 ModelView = Mesh * Camera;
  gl_Position = Projection * ModelView * vec4(vertexPosition_modelspace, 1);//vec4(vertexPosition_modelspace,1);//Projection * ModelView * vec4(vertexPosition_modelspace,1);

  UV = vertexUV;
}
