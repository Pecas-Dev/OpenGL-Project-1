#shader Vert
#version 330 core
		
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinate;

out vec2 vTextureCoordinates;

uniform mat4 uModelViewProjectionMatrix;
		
void main()
{
	gl_Position = uModelViewProjectionMatrix * position;
	vTextureCoordinates = textureCoordinate;
};


#shader Frag
#version 330 core
		
layout (location = 0) out vec4 color;

in vec2 vTextureCoordinates;

uniform vec4 uColor;
uniform sampler2D uTexture;
		
void main()
{
	vec4 textureColor = texture(uTexture, vTextureCoordinates);

	color = textureColor;
};