#version 100

attribute vec2 pos;
attribute vec2 texcoord;
varying vec2 vtexcoord;

void main()
{
    vtexcoord = texcoord;
    gl_Position = vec4(pos, 0.0, 1.0);
}
