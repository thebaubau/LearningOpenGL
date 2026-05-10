#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform bool  chaos;
uniform bool  confuse;
uniform bool  shake;
uniform float time;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f); 
    vec2 texture = aTexCoords;
    if (chaos)
    {
        float strength = 0.3;
        vec2 pos = vec2(texture.x + sin(time) * strength, texture.y + cos(time) * strength);        
        TexCoords = pos;
    }
    else if (confuse)
    {
        TexCoords = vec2(1.0 - texture.x, 1.0 - texture.y);
    }
    else
    {
        TexCoords = texture;
    }
    if (shake)
    {
        float strength = 0.01;
        TexCoords.x += cos(time * 10) * strength;        
        TexCoords.y += cos(time * 15) * strength;        
    }
}  