#include"keyboardObj.h"
#include"keyboard.h"
#include"check.h"
KeyboardObj::~KeyboardObj()
{
	ASSERT_LOG(!is_log_keyboard, "ERROR::KEYBOARDOBJ: " << id_name.getStr() << " "
		<< id_num << "isn't detached in keyboard");
}

void KeyboardObj::log_keyboard()
{
	if(!is_log_keyboard)
	{		
		std::function<void(int, int)> std_func = [this](int key, int action)
		{ this->processInput(key, action); };
		KeyBoard::log(std_func,	id_num);
	}
	is_log_keyboard = true;
}

void KeyboardObj::detach_keyboard()
{
	if (is_log_keyboard)
		KeyBoard::detach(id_num);
	is_log_keyboard = false;
}
