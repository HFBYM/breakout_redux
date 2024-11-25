#pragma once
/// @brief This is a singleton
class Game
{
public:
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;

	/// @brief get the reference of the only instance
	static Game& get_instance();
	
	void init();
	void run();
private:
	~Game();
	Game();
};
