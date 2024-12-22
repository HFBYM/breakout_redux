#include "ball.h"
#include "keyval.h"

/// @brief generate the ball range
static MoveObj **ball_range = nullptr;
//TODO randon speed
static const glm::vec2 init_ball_velocity(200.0f, -450.0f);

Ball::Ball(unsigned int screen_width, unsigned int screen_height, glm::vec3 color, float radius)
    : screen_height(screen_height), screen_width(screen_width), radius(radius), RenderObj("basketball", "sprite", color),
      Object(glm::vec2(0.0f), glm::vec2(2 * radius), "Ball")
{
    if (!ball_range)
    {
        ball_range = new MoveObj *[4];
        ball_range[0] = new MoveObj("Ball_Range", glm::vec2(-10.0f, 0.0f), glm::vec2(10.0f, screen_height));
        ball_range[1] = new MoveObj("Ball_Range", glm::vec2(screen_width, 0.0f), glm::vec2(10.0f, screen_height));
        ball_range[2] = new MoveObj("Ball_Range", glm::vec2(0.0f, -10.0f), glm::vec2(screen_width, 10.0f));
        ball_range[3] = new MoveObj("Ball_Range", glm::vec2(0.0f, screen_height), glm::vec2(screen_width, 10.0f));
        for (int i = 0; i < 4; i++)
        {
            ball_range[i]->log_collision();
        }
    }
}

Ball::~Ball()
{
    if (ball_range)
    {
        for (int i = 0; i < 4; i++)
        {
            if (ball_range[i])
            {
                ball_range[i]->detach_collision();
                delete ball_range[i];
            }
            ball_range[i] = nullptr;
        }
        delete[] ball_range;
        ball_range = nullptr;
    }
}

void Ball::log_all()
{
    log_collision();
    log_move();
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

void Ball::do_collision(const mString& message,const glm::vec2 &reflect, const glm::vec2 &offset)
{
    velocity = glm::reflect(velocity, glm::normalize(reflect) );
    pos += offset;
    if( message == "Player")
        velocity.y = -abs(velocity.y);
}
void Ball::processInput(int key, int action)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        if (isSticked)
        {
            isSticked = false;
            velocity = init_ball_velocity;
        }
        else
        {
            isSticked = true;
            velocity = glm::vec2(0.0f);
        }
    }
}

void Ball::setPos(const glm::vec2 &player_pos, const glm::vec2 &player_size)
{
    if (isSticked)
    {
        pos.x = player_pos.x + player_size.x / 2 - radius;
        pos.y = player_pos.y - 2 * radius;
    }
}
