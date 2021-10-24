#version 330 core

in vec4 vertexColor;
in vec2 vertexTextureCoordinates;

out vec4 fragmentColor;

uniform sampler2D fragmentTexture;

void main()
{
    fragmentColor = texture(fragmentTexture, vertexTextureCoordinates);
}