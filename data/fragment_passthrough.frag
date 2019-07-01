#version 100

precision mediump float;

varying vec2 vtexcoord;

uniform sampler2D tex;

void main()
{
    vec4 tc = texture2D(tex, vtexcoord);
    gl_FragColor = vec4(tc.rgb, 1.0);
}
