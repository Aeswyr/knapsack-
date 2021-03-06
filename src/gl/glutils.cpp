#include "knapsack/internal/glutils.h"

#include <string>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE

#include <knapsack/log.h>

unsigned int GLCompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (!status) {
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* message = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, message);
		out::log << out::err << message << out::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

void GLClearError() {
    while(glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogError(const char* function, const char* file, int line) {
    bool err = true;
    while(GLenum error = glGetError()) {
        out::log << out::err << "OpenGL function " << function << " in file " << file << " at line "
        << line << " failed, producing error number " << error << out::endl;
        err = false;
    }
    return err;
}