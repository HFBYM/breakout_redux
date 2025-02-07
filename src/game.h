#pragma once
#include <memory>
class Level;
class RenderObj;
class Player;
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

	std::unique_ptr<Level> level;
	std::unique_ptr<RenderObj> background;
	std::unique_ptr<Player> player_1;
	std::unique_ptr<Player> player_2;
};
