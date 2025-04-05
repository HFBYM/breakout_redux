#shader vertex
#version 330 core
// world coord and tex coord
layout(location = 0) in vec4 a_vertex;
out vec2 v_texCoord;
uniform mat4 u_model;
uniform mat4 u_proj;
void main()
{
	v_texCoord = a_vertex.zw;
	gl_Position = u_proj * u_model * vec4(a_vertex.xy, 0.0f, 1.0f);
}

#shader fragment
#version 330 core
in vec2 v_texCoord;
// tex sampler
uniform sampler2D u_image;
uniform vec4 u_spriteColor;
void main()
{
	gl_FragColor = vec4(u_spriteColor) * texture(u_image, v_texCoord);
}