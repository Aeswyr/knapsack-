#include "knapsack/internal/gl/indexbuffer.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE



IndexBuffer::IndexBuffer(const unsigned short* data, unsigned int count) : count(count) {
    glCreateBuffers(1, &RID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned short), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &RID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, RID);
}

void IndexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}