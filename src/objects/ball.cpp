/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 15:35:13
 * @FilePath: \breakout_redux\src\objects\ball.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "objects/ball.h"

#include "engines/particle_generator.h"
#include "engines/soundEngine.h"
#include "utils/random.h"

namespace ball
{
    namespace
    {
        constexpr float RADIUS = 25.0f;
    }
    struct Ball::BallData
    {
        bool isSticked = true;
        bool isThrough = false;
        const glm::vec3 init_color;
        std::function<void(int)> player_add_score;
        BallData(const glm::vec3 &init_color, std::function<void(int)> player_add_score)
            : init_color(init_color), player_add_score(player_add_score) {}
    };
    Ball::Ball(std::function<void(int)> player_add_score, const glm::vec3 &color)
        : RenderObj("basketball", "sprite", glm::vec4(color, 1.0f)),
          Object(glm::vec2(0.0f), glm::vec2(2 * RADIUS), "Ball"), MoveObj(glm::vec2(0.0f)),
          data(std::make_unique<BallData>(color, player_add_score))
    {
        using particle_generator::ParticleGenerator;
        using m_random::Random;
        constexpr float PI_FACTOR = (3.14159f / 180.0f);
        constexpr float start_theta = 40.0f * PI_FACTOR;
        constexpr float end_theta = 60.0f * PI_FACTOR;
        const float v_length = glm::length(glm::vec2(200.0f, 450.0f));

        float theta = Random::instance().randomFloat(end_theta - start_theta) + start_theta;
        glm::vec2 velocity;
        velocity.y = -v_length * glm::sin(theta);
        velocity.x = v_length * glm::cos(theta) * (Random::instance().randomInt(1) ? -1 : 1);

        setVelocity(velocity);
        ParticleGenerator::instance().log(getIdName(), getIdNum(),
            std::make_unique<particle_generator::ParticleData>(getPos(),
            velocity, getSize(), getColor(), false));
    }

    Ball::~Ball()
    {
        detach_collision();
        detach_move();
        detach_renderer();
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

    void Ball::do_collision(const std::string &message,
        const glm::vec2 &reflect, const glm::vec2 &offset)
    {
        using sound_engine::SoundEngine;
        auto velocity = getVelocity();
        auto pos = getPos();
        if (message == "Brick")
        {
            if (!data->isThrough)
            {
                velocity = glm::reflect(velocity, glm::normalize(reflect));
                pos += offset;
            }
            data->player_add_score(1);
        }
        else if (message == "Brick_Solid")
        {
            velocity = glm::reflect(velocity, glm::normalize(reflect));
            pos += offset;
        }
        else if (message == "Ball_Range")
        {
            velocity = glm::reflect(velocity, glm::normalize(reflect));
            pos += offset;
            if (reflect == glm::vec2(0, -1))
            {
                data->player_add_score(-2);
                data->isSticked = true;
            }
        }
        else if (message == "Pad")
        {
            velocity = glm::reflect(velocity, glm::normalize(reflect));
            pos += offset;
            velocity.y = -abs(velocity.y);
            if (!data->isSticked)
                SoundEngine::instance().play_music("BLEEPWAV");
        }
        Object:: setPos(pos);
        setVelocity(velocity);
    }

    void Ball::processInput(int key, bool press)
    {
        if (press)
        {
            if (data->isSticked)
            {
                data->isSticked = false;
                log_move();
                log_collision();
            }
        }
    }

    void Ball::setPos(const glm::vec2 &pad_pos, const glm::vec2 &pad_size,
         unsigned int screen_width, unsigned int screen_height)
    {
        if (data->isSticked)
        {
            glm::vec2 pos = getPos();
            pos.x = pad_pos.x + pad_size.x / 2 - RADIUS;
            pos.y = pad_pos.y - 2 * RADIUS;
            Object::setPos(pos);
            glm::vec2 velocity = getVelocity();
            velocity.y = -abs(velocity.y);
            setVelocity(velocity);
            detach_move();
            detach_collision();
        }
        else
        {
            glm::vec2 pos = getPos();
            if (pos.x < 0.0f)
                pos.x = 0.0f;
            else if (pos.x + 2 * RADIUS > screen_width)
                pos.x = screen_width - 2 * RADIUS;
            if (pos.y < 0.0f)
                pos.y = 0.0f;
            else if (pos.y + 2 * RADIUS > screen_height)
                pos.y = screen_height - 2 * RADIUS;
            Object::setPos(pos);
        }
    }

    void Ball::setSticked(bool sticked)
    {
        data->isSticked = sticked;
    }
    void Ball::setThrough(bool through)
    {
        data->isThrough = through;
    }
    void Ball::resetColor()
    {
        auto temp = getColor();
        RenderObj::setColor(glm::vec4(data->init_color, temp.a));
    }
    void Ball::setStealth(bool stealth)
    {
        using particle_generator::ParticleGenerator;
        auto color = getColor();
        color.a = stealth ? 0.0f : 1.0f;
        RenderObj::setColor(color);
        if (stealth)
            ParticleGenerator::instance().detach(getIdName(), getIdNum());
        else
            ParticleGenerator::instance().log(getIdName(), getIdNum(),
            std::make_unique<particle_generator::ParticleData>(getPos(),
            getVelocity(), getSize(), getColor(), false));
    }
} // namespace ball
