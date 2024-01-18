#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 lights_direction[10];
uniform vec3 lights_position[10];
uniform vec3 lights[10];
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 light_direction2;
uniform vec3 light_position2;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int switchSpotLight;
uniform float spotAngle;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float calcul(vec3 L, vec3 light_direction_f) {
    float cut_off = radians(spotAngle);
    float spot_light = dot(-L, light_direction_f);
    float light_att_factor = 0;
    float spot_light_limit = cos(cut_off);

    if (spot_light > cos(cut_off))
    {
        float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
        light_att_factor = pow(linear_att, 2);
    } else {
        light_att_factor = 0;
    }
    return light_att_factor;
}


void main()
{
    vec3 V = normalize( eye_position - world_position );
    vec3 L = normalize( light_position - world_position );
    vec3 L2 = normalize( light_position2 - world_position );
    vec3 H = normalize( L + V );
    vec3 H2 = normalize( L2 + V );
    vec3 N = normalize(world_normal);
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    float diffuse_light = material_kd * 1 * max (dot(N,L), 0);
    float diffuse_light2 = material_kd * 1 * max (dot(N,L2), 0);
    float specular_light = 0;
    float specular_light2 = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
    specular_light = material_ks * 1 * 1 * pow(max(dot(N, H), 0), material_shininess);
    specular_light2 = material_ks * 1 * 1 * pow(max(dot(N, H2), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    // Light 2



    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    // TODO(student): Write pixel out color
    float d = distance(light_position, world_position);
    float factorAtenuare = 1 / (1 + 0.14 * d + 0.07 * d * d);
    float d2 = distance(light_position2, world_position);
    float factorAtenuare2 = 1 / (1 + 0.14 * d2 + 0.07 * d2 * d2);
    vec3 color;
    if (switchSpotLight == 1) {
        factorAtenuare = calcul(L, light_direction);
        factorAtenuare2 = calcul(L2, light_direction2);
    }   else {
    }
    color = object_color * (ambient_light + (factorAtenuare * (diffuse_light + specular_light)) + (factorAtenuare2 * (diffuse_light2 + specular_light2)));
    out_color = vec4(color, 1);
}