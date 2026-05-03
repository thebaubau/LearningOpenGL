#version 460 core

layout (location = 0) in vec2 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 tex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;

void main()
{
    float scale = 15.0f;
    TexCoords = tex;
    ParticleColor = color;
    gl_Position = projection * vec4((vertex * scale) + offset, 0.0, 1.0);
}