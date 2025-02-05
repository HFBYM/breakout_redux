#include"keyboard.h"
#include"debug.h"
#include<glad.h>
#include<glfw3.h>

void KeyBoard:: key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// close the window when esc pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		MDEBUG();
	else if (action == GLFW_PRESS || action == GLFW_RELEASE)
	{
		for (auto& [id, data] : data["Pad"])
			data->func_p(key, action);
		for (auto& [id, data] : data["Ball"])
			data->func_p(key, action);
	}
	else
		return;
}