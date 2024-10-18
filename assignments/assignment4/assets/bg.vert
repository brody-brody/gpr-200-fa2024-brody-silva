#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float uniTime;

void main()
{
    // position is blown up to stretch across screen
    gl_Position = vec4(aPos.x * 10, aPos.y * 10, aPos.z, 1.0f);
    ourColor = aColor;
    TexCoord = aTexCoord + vec2(uniTime / 25, uniTime / 25);

    // repeating texture to cover the screen
    TexCoord = TexCoord * 25;
}