/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 10:41:12
 * @FilePath: \breakout_redux\src\engines\keyboard.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <glad.h>
#include <glfw3.h>

#include <functional>

#include "resource_manage/logger.h"

namespace keyboard
{
	struct KeyBoardData
	{
		using FuncType = std::function<void(int, int)>;
		FuncType func_p;
		explicit KeyBoardData(FuncType func_p) : func_p(func_p) {}
	};

	/// @brief store and process the keyboard input
	class KeyBoard : public logger::Logger<KeyBoardData>
	{
	public:
		/// @brief store the callback function
		/// @brief mention	that it won't work when more than 3 keys pressed, it might be due to GLFW
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

		static KeyBoard &instance()
		{
			static KeyBoard inst;
			return inst;
		}

	private:
		KeyBoard() = default;
		~KeyBoard() = default;
	};
} // namespace keyboard
