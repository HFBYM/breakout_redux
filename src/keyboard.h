#pragma once
#include <functional>
#include "logger.h"
struct GLFWwindow;

struct KeyBoardData
{
	using FuncType = std::function<void(int, int)>;

	FuncType func_p;
	KeyBoardData(FuncType func_p) : func_p(func_p) {}
};

/// @brief store and process the keyboard input
class KeyBoard:public Logger<KeyBoardData>
{
public:
	/// @brief this function type is used for callback
	using FuncType = KeyBoardData::FuncType;

	using Data = KeyBoardData;

	/// @brief store the callback function
	/// @brief mention	that it won't work when more than 3 keys pressed, it might be due to GLFW
	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

	static KeyBoard& instance()
	{
		static KeyBoard inst;
		return inst;
	}
private:
	KeyBoard() = default;
	~KeyBoard() = default;
};
