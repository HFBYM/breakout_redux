/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-22 21:37:30
 * @FilePath: \breakout_redux\src\utils\debug.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "utils/debug.h"

#include <glad.h>
#include <glfw3.h>

#include <iostream>
namespace debug{
/// @brief this function will ignore errors before to fucos on following errors
void clearError()
{
	while (glGetError() != GL_NO_ERROR)
	{
	}
	// there are many types of errors. Some are set when errors happen.
	// glGetError returns one of the flags of happened errors and resets it
}

void check(const char *file, int line)
{
	char *type = nullptr;
	GLuint error = glGetError();
	if (error == GL_NO_ERROR)
		return;
	else
	{
		do
		{
			switch (error)
			{
			case GL_INVALID_ENUM:
				type = "invalid_enum";
				break;
			case GL_INVALID_VALUE:
				type = "invalid_value";
				break;
			case GL_INVALID_OPERATION:
				type = "invalid_operation";
				break;
			case GL_OUT_OF_MEMORY:
				type = "out_of_memory";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				type = "invalid_framebuffer_operation";
				break;
			default:
				type = "unamed_error";
				break;
			}
			std::cerr << "ERROR::OPENGL:" << type << "\tFile:"
					  << file << "\tLine:" << line << std::endl;
		} while (error = glGetError() != GL_NO_ERROR);
	}
	MDEBUG();
}
} // namespace debug
