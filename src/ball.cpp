#include"ball.h"

Ball::Ball(unsigned int screen_width, unsigned int screen_height, glm::vec3 color, float radius)
:screen_height(screen_height), screen_width(screen_width), radius(radius), RenderObj("basketball","sprite",color),
Object(glm::vec2(0.0f), glm::vec2(2*radius),"Ball")
{
    
}

void Ball::log_all()
{
    log_collision();
    log_move();
    log_renderer();
}

void Ball::detach_all()
{
    detach_collision();
    detach_move();
    detach_renderer();
}

void Ball::setPos(const glm::vec2 &player_pos, const glm::vec2 &player_size)
{
    pos.x = player_pos.x + player_size.x/2 - radius;
    pos.y = player_pos.y - 2*radius;
}
