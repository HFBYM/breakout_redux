#pragma once
#include"pad.h"
#include"ball.h"
#include"keyboardObj.h"
#include<memory>
class Player: public KeyboardObj
{
public:
    enum class PlayerID {Player_Single, Player1, Player2 };
    
    /// @brief the id should be unique globally
    Player(unsigned int screen_width, unsigned int screen_height, PlayerID player_id = PlayerID::Player_Single);
    ~Player();

    void log_all();
    void detach_all();
    void update(float dt);

private:
    float pass_through_t = 0.0f;
    float chaos_t = 0.0f;
    float icy_t = 0.0f;
    float stealth_t = 0.0f;

    std::unique_ptr<Pad> pad;
    std::unique_ptr<Ball> ball;
    static std::unique_ptr<std::unique_ptr<MoveObj>[]> range;
    PlayerID player_id;

    virtual void processInput(int key, int action) override;
    void buff_process(unsigned int id);

    static glm::vec3 getColor(PlayerID player_id);
    static glm::vec2 getPos(unsigned int screen_width, unsigned int screen_height, PlayerID player_id);
};