#shader vertex
#version 330 core
// world coord and tex coord
layout(location = 0) in vec4 vertex;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 proj;
void main()
{
	texCoord = vertex.zw;
	gl_Position = proj * model * vec4(vertex.xy, 0.0f, 1.0f);
}

#shader fragment
#version 330 core
in vec2 texCoord;
// tex sampler
uniform sampler2D image;
uniform vec4 spriteColor;
void main()
{
	gl_FragColor = vec4(spriteColor) * texture(image, texCoord);
}