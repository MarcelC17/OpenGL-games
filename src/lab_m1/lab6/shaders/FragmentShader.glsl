#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

// Output
 out vec4 out_color;
 out vec3 out_texture;
 out vec4 out_normal;


void main()
{
    out_color = vec4(frag_color, 1);
    out_texture = vec3(frag_texture, 1);
    out_normal = vec4(frag_normal, 1);

}
