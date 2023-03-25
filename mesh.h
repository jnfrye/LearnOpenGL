#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void BufferVertexData(unsigned int vertexArraySize, GLfloat vertexArray[], unsigned int elementArraySize, unsigned int elementArray[], unsigned int& vao, unsigned int& vbo, unsigned int& ebo);