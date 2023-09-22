$input a_position, a_normal, a_texcoord0
$output v_texcoord0, v_normal, v_fragPosition

#include <bgfx_shader.sh>

uniform mat4 u_ProjView;
uniform mat4 u_Model;
uniform mat4 u_InverseModel;

void main()
{
	gl_Position = mul(mul(u_ProjView, u_Model), vec4(a_position, 1.0));
	v_texcoord0 = a_texcoord0;
	v_normal = mul(transpose(u_InverseModel), a_normal);
	v_fragPosition = mul(u_Model, vec4(a_position, 1.0)).xyz;
}