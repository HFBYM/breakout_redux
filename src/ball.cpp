#include "ball.h"
#include "particle_generator.h"
#include "soundEngine.h"
#include "random.h"

Ball::Ball(glm::vec3 color, float radius)
    : radius(radius), RenderObj("basketball", "sprite", glm::vec4(color, 1.0f)), Object(glm::vec2(0.0f), glm::vec2(2 * radius), "Ball"), init_color(color)
{
#define PI_FACTOR (3.14159f / 180.0f)
    float start_theta = 40.0f * PI_FACTOR;
    float end_theta = 80.0f * PI_FACTOR;
    float theta = Random::instance().randomFloat(end_theta - start_theta) + start_theta;
    velocity.y = -glm::length(glm::vec2(200.0f, 450.0f)) * glm::sin(theta);
    velocity.x = glm::length(glm::vec2(200.0f, 450.0f)) * glm::cos(theta) * (Random::instance().randomInt(1) ? -1 : 1);
    ParticleGenerator::instance().log(id_name, id_num, std::make_unique<ParticleGenerator::Data>(pos, velocity, size, this->color, false));
#undef PI_FACTOR
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

void Ball::do_collision(const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
    if (!isThrough || message == "Ball_Range")
    {
        velocity = glm::reflect(velocity, glm::normalize(reflect));
        pos += offset;
    }
    if (message == "Pad")
    {
        velocity = glm::reflect(velocity, glm::normalize(reflect));
        pos += offset;
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