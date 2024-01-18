#version 330

// Input
// TODO(student): Get color value from vertex shader
in vec3 color;
flat in int health;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    if (health == 3){
        out_color = vec4(color,1);
    }
    else if(health == 2){
        out_color = vec4(color * 0.8,1);
    } else if(health <= 1){
        out_color = vec4(color * 0.6,1);
    }
}
