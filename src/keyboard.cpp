#include"keyboard.h"
#include<glad.h>
#include<glfw3.h>
#include"check.h"

static bool isClear = false;

/// @brief to call a member func needs an instance but with lambda it's easy
std::map<mString, std::map<unsigned int, KeyBoard::LogData*>>* log_datas = new std::map<mString, std::map<unsigned int, KeyBoard::LogData*>>;
Logger<KeyBoard::LogData> KeyBoard::logger(*log_datas);

void KeyBoard:: key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	ASSERT_LOG(!isClear, "ERROR::KEYBOARD: " << __FUNCTION__ << " uses keyboard cleared");
	// close the window when esc pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		__debugbreak();
	else if (action == GLFW_PRESS || action == GLFW_RELEASE)
	{
		for (auto& [id, data] : (*log_datas)["Player"])
				data->func_p(key, action);
	}
}

void KeyBoard::clear()
{
	ASSERT_LOG(!isClear, "ERROR::KEYBOARD: " << __FUNCTION__ << " uses keyboard cleared");
	isClear = true;
	logger.clear();
	if(log_datas)
		delete log_datas;
	log_datas = nullptr;
}
