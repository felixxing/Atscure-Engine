#version 450 core

layout(location = 0) out vec4 albedo;
layout(location = 1) out vec4 specular;
layout(location = 2) out vec4 position;
layout(location = 3) out vec4 normal;

layout(location = 0) in struct
{
    vec3 position;
    vec3 normal;
    vec3 uv;
    vec3 color;
    vec3 specular;
} frag_data;

layout(binding = 1) uniform sampler2D albe_tex;
layout(binding = 2) uniform sampler2D spec_tex;
layout(binding = 3) uniform sampler2D opac_tex;

void main()
{
    albedo = vec4(frag_data.color, 1.0);
    specular = vec4(frag_data.specular, 1.0);
    position = vec4(frag_data.position, 1.0);
    normal = vec4(frag_data.normal, 1.0);
}