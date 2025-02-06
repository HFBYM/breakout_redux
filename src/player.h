#pragma once
#include"pad.h"
#include"ball.h"
#include"keyboardObj.h"
class Player: public KeyboardObj
{
public:
    Player(unsigned int screen_width, unsigned int screen_height, glm::vec3 color = glm::vec3(1.0f));
    ~Player();

    void log_all();
    void detach_all();
    void update(float dt);

    // TODO 整合两个range pad ball
private:
    float pass_through_t = 0.0f;
    float chaos_t = 0.0f;
    float icy_t = 0.0f;
    float stealth_t = 0.0f;

    std::unique_ptr<Pad> pad;
    std::unique_ptr<Ball> ball;
    static std::unique_ptr<std::unique_ptr<MoveObj>[]> range;

    virtual void processInput(int key, int action) override;
    void buff_process(unsigned int id);
};