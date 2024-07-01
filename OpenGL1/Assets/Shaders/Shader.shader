#shader Vert
#version 330 core
		
layout (location = 0) in vec4 position;
		
void main()
{
	gl_Position = position;
};


#shader Frag
#version 330 core
		
layout (location = 0) out vec4 color;

uniform vec4 uColor;
		
void main()
{
	color = uColor;
};