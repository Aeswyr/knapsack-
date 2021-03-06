#include "knapsack/internal/gl/vertexbuffer.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE



VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glCreateBuffers(1, &RID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &RID);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, RID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}