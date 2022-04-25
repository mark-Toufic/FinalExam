#version 430

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec4 outColor;

uniform layout(binding = 0) sampler2D s_Image;
uniform layout(binding = 1) sampler1D s_ToonTerm;

void main() {	
	// Get albedo from the material
	vec4 albedoColor = texture(s_Image, inUV);

    // split up albedo channels and apply our 1D sampler of our Toon LUT
    albedoColor.r = texture(s_ToonTerm, albedoColor.r).r;
    albedoColor.g = texture(s_ToonTerm, albedoColor.g).g;
    albedoColor.b = texture(s_ToonTerm, albedoColor.b).b;
	albedoColor.a = 1.0;

	outColor = albedoColor;

}