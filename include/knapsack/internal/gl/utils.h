#include "knapsack/internal/gl/utils.h"

#include <string>

unsigned int GLCompileShader(unsigned int type, const std::string& source);

void GLClearError();

bool GLLogError(const char* function, const char* file, int line);