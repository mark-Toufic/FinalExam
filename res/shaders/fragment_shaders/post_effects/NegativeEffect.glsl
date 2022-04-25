#version 430

layout(location = 0) in vec2 inUV;

layout(location = 0) out vec3 outColor;

uniform layout(binding = 0) sampler2D s_Image;
uniform layout(binding = 1) sampler3D s_Lut;

uniform float u_Strength;
//The bool variable for when the player is at low health
//passed in from NegativeEffect.cpp
//uniform bool u_Lowhealth;

void main() {
    vec3 color = texture(s_Image, inUV).rgb;

   // the code we use for when we have our low health variable
   //if (u_LowHealth == true)
   //{
   //    outColor = vec3(1.0f) - color;
   //}
   // just takes in the input color and outputs the inverse
   outColor = vec3(1.0f) - color;

}