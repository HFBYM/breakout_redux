#shader vertex
#version 330 core
layout(location = 0) in vec4 vertex;
out vec2 texCoord;
uniform bool chaos;
uniform bool confuse;
uniform bool shake;
uniform float time;	//ϵͳ��ǰʱ��
void main()
{
	gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
	vec2 tex = vertex.zw;	//��������
	if (chaos)
	{
		float strength = 0.3;
		vec2 pos = vec2(tex.x + sin(time) * strength, tex.y + cos(time) * strength);
		texCoord = pos;		//ͨ����ת֡�������������ﵽ��ͷ��ת��Ч�� ��λ�ûᵼ������������
	}
	else if (confuse)
		texCoord = vec2(1.0 - tex.x, 1.0 - tex.y);
	else
		texCoord = tex;
	if (shake)
	{
		float strength = 0.01;
		gl_Position.x += cos(time * 10) * strength;
		gl_Position.y += cos(time * 15) * strength;		//������ᵼ�³�������
	}
}

#shader fragment
#version 330 core
in vec2 texCoord;				//���ֵ���в�ȫ
uniform bool chaos;				//���ߵ�uniform������ͨ
uniform bool confuse;
uniform bool shake;
uniform bool blurry;

uniform sampler2D scene;
uniform vec2 offset[9];			//���ڼ���ƫ�Ƶ�����		��Щ�������ⲿ���д��ݶ�����ÿ����ɫ��������һ��
uniform int edge_kernel[9];		//��Ե�����
uniform float blur_kernel[9];	//ģ�������
void main()
{
	gl_FragColor = vec4(0.0f);
	vec3 samples[9];	//�Ȱ�������Χ����ɫ����
	if (chaos || shake || blurry)
		for (int i = 0; i < 9; i++)
			samples[i] = vec3(texture(scene, texCoord + offset[i]));
	if (chaos)
	{
		for (int i = 0; i < 9; i++)
			gl_FragColor += vec4(samples[i] * edge_kernel[i], 0.0f);
		gl_FragColor.a = 1.0f;
	}
	else if (confuse)
		gl_FragColor = vec4(1 - texture(scene, texCoord).rgb, 1.0f);	//��ת��ɫ
	else if (shake || blurry)
	{
		for (int i = 0; i < 9; i++)
			gl_FragColor += vec4(samples[i] * blur_kernel[i], 0.0f);
		gl_FragColor.a = 1.0f;
	}
	else
		gl_FragColor = texture(scene, texCoord);
}