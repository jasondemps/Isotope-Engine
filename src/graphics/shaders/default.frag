#version 330 core

// Get interpolated values from vertex shaders
in vec2 UV;

// Output data
out vec4 color;

// Constant values for mesh
uniform sampler2D texSampler;

void main()
{
    //color = texture2D(texSampler, UV);

    color = vec4(1.0, 1.0, 1.0, 1.0);
}
