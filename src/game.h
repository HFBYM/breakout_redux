#pragma once
#include <memory>
#include<vector>
class Level;
class RenderObj;
class Player;
class Menu;
struct GLFWwindow;
/// @brief This is a singleton rather than a static one cause some functions can't be called anywhere
class Game
{
public:
	/// @brief get the reference of the only instance
	static Game &get_instance()
	{
		static Game m_game;
		return m_game;
	}

	/// @brief make sure Game is initialized before running
	void run();

private:
	Game();
	/// @brief if this function is public then the singleton can be delete without reconstruction
	~Game();

	Game(const Game &) = delete;
	Game &operator=(const Game &) = delete;

	GLFWwindow *window = nullptr;
	int monitor_width, monitor_height = 0;

	std::unique_ptr<Level> level = nullptr;
	std::unique_ptr<RenderObj> background = nullptr;
	std::unique_ptr<Menu> menu = nullptr;
	std::vector<std::unique_ptr<Player>> players;


	void onGame(int start_menu_choice, int level_choice);
};
