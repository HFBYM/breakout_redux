#include "keyboardObj.h"
#include "keyboard.h"
KeyboardObj::~KeyboardObj()
{
	detach_keyboard();
}

void KeyboardObj::log_keyboard()
{
	if (!is_log_keyboard)
	{
		KeyBoard::FuncType func = [this](int key, int action)
		{ this->processInput(key, action); };
		KeyBoard::instance().log(id_name, id_num, std::make_unique<KeyBoard::Data>(func));
	}
	is_log_keyboard = true;
}

void KeyboardObj::detach_keyboard()
{
	if (is_log_keyboard)
		KeyBoard::instance().detach(id_name, id_num);
	is_log_keyboard = false;
}
