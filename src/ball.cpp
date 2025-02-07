#include "ball.h"
#include "particle_generator.h"
#include "soundEngine.h"
// TODO randon speed and delete
static const glm::vec2 init_ball_velocity(200.0f, -450.0f);

Ball::Ball(glm::vec3 color, float radius)
    : radius(radius), RenderObj("basketball", "sprite", glm::vec4(color, 1.0f)), Object(glm::vec2(0.0f), glm::vec2(2 * radius), "Ball"), init_color(color)
{
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
}

void Ball::detach_all()
{
    detach_collision();
    detach_move();
    detach_renderer();
}

void Ball::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
    if (!isThrough || message == "Ball_Range" || message == "Pad")
    {
        velocity = glm::reflect(velocity, glm::normalize(reflect));
        pos += offset;
    }
    if (message == "Pad")
    {
        velocity.y = -abs(velocity.y);
        if (!isSticked)
            SoundEngine::instance().play_music(SoundEngine::Song::BLEEPWAV);
    }
}

void Ball::processInput(int key, bool press)
{
    if (press)
    {
        if (isSticked)
        {
            isSticked = false;
            log_move();
            log_collision();
        }
        else
        {
            isSticked = true;
            detach_move();
            detach_collision();
        }
    }
}

void Ball::setPos(const glm::vec2 &pad_pos, const glm::vec2 &pad_size)
{
    if (isSticked)
    {
        pos.x = pad_pos.x + pad_size.x / 2 - radius;
        pos.y = pad_pos.y - 2 * radius;
        detach_move();
        detach_collision();
    }
}

void Ball::setStealth(bool stealth)
{
    color.a = stealth ? 0.0f : 1.0f;
    if (stealth)
        ParticleGenerator::instance().detach(id_name, id_num);
    else
        ParticleGenerator::instance().log(id_name, id_num, std::make_unique<ParticleGenerator::Data>(pos, velocity, size, this->color, false));
}