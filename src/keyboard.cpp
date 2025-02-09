#include"keyboard.h"
#include"debug.h"
#include<glad.h>
#include<glfw3.h>

void KeyBoard:: key_callback(GLFWwindow* window, int m_key, int scancode, int action, int mode)
{
	// close the window when esc pressed
	if (m_key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwHideWindow(window);

		// break the loop
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (m_key == GLFW_KEY_P && action == GLFW_PRESS)
		MDEBUG();
	else if (action == GLFW_PRESS || action == GLFW_RELEASE)
	{
		for(auto&[id, player]:data["Player"])
			player->func_p(m_key, action);
	}
	else
		return;
}