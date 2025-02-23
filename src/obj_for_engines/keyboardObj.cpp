/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:03:29
 * @FilePath: \breakout_redux\src\obj_for_engines\keyboardObj.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "obj_for_engines/keyboardObj.h"

#include <memory>

#include "engines/keyboard.h"
namespace keyboard_obj
{
	KeyboardObj::~KeyboardObj()
	{
		detach_keyboard();
	}
	KeyboardObj::KeyboardObj():Object("KeyboardObj")
	{
	}
	void KeyboardObj::log_keyboard()
	{
		using keyboard::KeyBoard;
		if (!is_log_keyboard)
		{
			auto func = [this](int key, int action)
			{ this->processInput(key, action); };
			KeyBoard::instance().log(getIdName(), getIdNum(),
									 std::make_unique<keyboard::KeyBoardData>(func));
		}
		is_log_keyboard = true;
	}

	void KeyboardObj::detach_keyboard()
	{
		using keyboard::KeyBoard;
		if (is_log_keyboard)
			KeyBoard::instance().detach(getIdName(), getIdNum());
		is_log_keyboard = false;
	}
} // namespace keyboard_obj
