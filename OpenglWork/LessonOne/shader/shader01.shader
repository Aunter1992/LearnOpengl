#shader vertex
#version 330 core
layout(location=0) in  vec4 position;
layout(location = 1) in  vec2 uv_Pos;

out vec2 uv;
void main()
{
	uv = uv_Pos;
	gl_Position=position;
};

#shader fragment
#version 330 core

layout(location=0) out  vec4 col;

in vec2 uv;

uniform vec4 u_Color;
uniform sampler2D tex;
void main()
{
	vec4 co = texture(tex, uv);
	col = co;
};