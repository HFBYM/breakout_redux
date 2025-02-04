#include "ball.h"
#include "keyval.h"
#include "particle_generator.h"
#include "soundEngine.h"
#include <iostream>

std::unique_ptr<std::unique_ptr<MoveObj>[]> Ball::ball_range(std::make_unique<std::unique_ptr<MoveObj>[]>(4));
// TODO randon speed and delete
static const glm::vec2 init_ball_velocity(200.0f, -450.0f);

Ball::Ball(unsigned int screen_width, unsigned int screen_height, glm::vec3 color, float radius)
    : screen_height(screen_height), screen_width(screen_width), radius(radius), RenderObj("basketball", "sprite", glm::vec4(color, 1.0f)), Object(glm::vec2(0.0f), glm::vec2(2 * radius), "Ball")
{
    static bool is_init_range = false;
    if (!is_init_range)
    {
        ball_range[0] = std::make_unique<MoveObj>("Ball_Range", glm::vec2(-10.0f, 0.0f), glm::vec2(10.0f, screen_height));
        ball_range[1] = std::make_unique<MoveObj>("Ball_Range", glm::vec2(screen_width, 0.0f), glm::vec2(10.0f, screen_height));
        ball_range[2] = std::make_unique<MoveObj>("Ball_Range", glm::vec2(0.0f, -10.0f), glm::vec2(screen_width, 10.0f));
        ball_range[3] = std::make_unique<MoveObj>("Ball_Range", glm::vec2(0.0f, screen_height), glm::vec2(screen_width, 10.0f));
        for (int i = 0; i < 4; i++)
            ball_range[i]->log_collision();
    }
    is_init_range = true;
    velocity = init_ball_velocity;
    ParticleGenerator::instance().log(id_name, id_num, std::make_unique<ParticleGenerator::Data>(pos, velocity, size, this->color, false));
}

Ball::~Ball()
{
    detach_all();
}

void Ball::log_all()
{
    log_renderer();
    log_keyboard();
}

void Ball::detach_all()
{
    detach_collision();
    detach_move();
    detach_renderer();
    detach_keyboard();
}

void Ball::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
    velocity = glm::reflect(velocity, glm::normalize(reflect));
    pos += offset;
    if (message == "Player")
    {
        velocity.y = -abs(velocity.y);
        std::cout << "Ball is collided with " << message.getStr() << std::endl;
        if (!isSticked)
            SoundEngine::instance().play_music(SoundEngine::Song::BLEEPWAV);
    }
}
void Ball::processInput(int key, int action)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        if (isSticked)
        {
            isSticked = false;

            log_move();
            log_collision();

            static bool once = true;
            if (once)
                once = false;
        }
        else
        {
            isSticked = true;
            detach_move();
            detach_collision();
        }
    }
}
// TODO 双人模式绑定挡板
void Ball::setPos(const glm::vec2 &player_pos, const glm::vec2 &player_size)
{
    if (isSticked)
    {
        pos.x = player_pos.x + player_size.x / 2 - radius;
        pos.y = player_pos.y - 2 * radius;
    }
}
