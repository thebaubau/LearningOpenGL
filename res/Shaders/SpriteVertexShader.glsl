#version 460 core
layout (location = 0) in vec2 vertex; // <vec2 position>
layout (location = 1) in vec2 tex;    // <vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = tex;
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
}