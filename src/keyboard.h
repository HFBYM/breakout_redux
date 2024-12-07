# pragma once
#include<functional>
#include"logger.h"
struct GLFWwindow;
class KeyboardObj;
/// @brief store and process the keyboard input
class KeyBoard
{
public:
	/// @brief this function type is used for callback
	using FuncType = std::function<void(int,int)>;

	struct LogData
	{
		FuncType func_p;
		LogData(FuncType func_p) : func_p(func_p) {}
	};
	
	static Logger<LogData> logger;

	/// @brief mention	that it won't work when more than 3 keys pressed, it might be due to GLFW
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	/// @brief it can't clear one more time
	static void clear();
private:
	KeyBoard() = delete;
	~KeyBoard() = delete;
};
