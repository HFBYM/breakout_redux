#include"keyboard.h"
#include<glad.h>
#include<glfw3.h>
#include<vector>
static std::vector<KeyBoard::process_func_ptr> functions_ptr;
void KeyBoard:: key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// close the window when esc pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS || action == GLFW_RELEASE)
		for (auto& func_p : functions_ptr)
			func_p(key, action);
}
void KeyBoard:: set_process(process_func_ptr func_p)
{
	if(func_p)
		functions_ptr.push_back(func_p);
}