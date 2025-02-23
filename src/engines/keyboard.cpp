/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 10:41:25
 * @FilePath: \breakout_redux\src\engines\keyboard.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "engines/keyboard.h"
#include "utils/debug.h"
namespace keyboard
{
	void KeyBoard::key_callback(GLFWwindow *window, int m_key, int scancode, int action, int mode)
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
			const auto& data = getData();
			for (auto &[id, player] : data.at("Player"))
				player->func_p(m_key, action);
		}
		else
			return;
	}
} // namespace keyboard
