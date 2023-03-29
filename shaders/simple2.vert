// Must specify the GLSL version number; this matches the OpenGL version number
// Note we specify "core" as well
#version 330 core

// We must declare all vertex attributes
// For our first shader we only care about the position, so we have a single attribute
// - GLSL has "vector" data types vec1 through vec4 depending on how many coordinates you want
// - The "in" keyword is kinda boilerplate I think??? I think it means its an input??
// - In the last place we specify the name for the attribute.
// - Not sure what "location" is...
layout (location = 0) in vec3 aPos;

// Our lil' program has a main function! Cute!
void main()
{
    // The vertex shader must put the final vertex position in the pre-defined variable gl_Position
    // - Don't worry about the w-coord... for now ;)
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    // Although we have just passed the coordinates along (because our inputs use NDC),
    // usually the coordinates are NOT in NDC, and part of the vertex shader's job is doing that.
}