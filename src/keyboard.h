# pragma once
struct GLFWwindow;

/// @brief store and process the keyboard input
class KeyBoard
{
public:
	using process_func_ptr = void (*) (int key, int action);
	/// @brief mention	that it won't work when more than 3 keys pressed, it might be due to GLFW
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	/// @brief set the func_p as one of the callback
	static void set_process(process_func_ptr func_p);
private:
	KeyBoard() = default;
	~KeyBoard() = default;
};
