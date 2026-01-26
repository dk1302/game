#version 330 core
out vec4 FragColor;
in vec2 ourTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float colorOffset;
vec2 FlippedTexCoord;

void main()
{
  FlippedTexCoord = vec2(1.0 - ourTexCoord.x, ourTexCoord.y);
  FragColor = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), 0.2);
  // FragColor = texture(texture1, ourTexCoord);
}
