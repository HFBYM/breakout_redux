#pragma once
#include"glm.hpp"
#include"logger.h"
class Movement
{
public:
struct LogData
{
	glm::vec2& pos;
	glm::vec2& volecity;
	glm::vec2& accelerate;
	LogData(glm::vec2& pos, glm::vec2& volecity, glm::vec2& accelerate):pos(pos), volecity(volecity), accelerate(accelerate){}
};
private:
    ~Movement() = delete;
    Movement() = delete;
public:
    static Logger<LogData> logger;

    static void move(float dt);

    /// @brief it can't be cleared twice
    static void clear();
};
