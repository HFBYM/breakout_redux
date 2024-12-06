#include"keyboard.h"
#include<glad.h>
#include<glfw3.h>
#include<map>
#include"check.h"

static bool isClear = false;

/// @brief to call a member func needs an instance but with lambda it's easy
std::map<unsigned int, KeyBoard::FuncType> id_func;

void KeyBoard:: key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	ASSERT_LOG(!isClear, "ERROR::KEYBOARD: " << __FUNCTION__ << " uses keyboard cleared");
	// close the window when esc pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		__debugbreak();
	else if (action == GLFW_PRESS || action == GLFW_RELEASE)
		for (auto& [id, obj_func] : id_func)
				obj_func(key, action);
}

void KeyBoard::log(FuncType func, unsigned int id)
{
	ASSERT_LOG(!isClear, "ERROR::KEYBOARD: " << __FUNCTION__ << " uses keyboard cleared");
	if (func)
		id_func[id] = func;
}

void KeyBoard::detach(unsigned int id)
{
	ASSERT_LOG(!isClear, "ERROR::KEYBOARD: " << __FUNCTION__ << " uses keyboard cleared");
	id_func.erase(id);
}

void KeyBoard::clear()
{
	ASSERT_LOG(!isClear, "ERROR::KEYBOARD: " << __FUNCTION__ << " uses keyboard cleared");
	id_func.clear();
	isClear = true;
}
