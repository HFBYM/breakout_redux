/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 13:17:01
 * @FilePath: \breakout_redux\src\engines\particle_generator.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "engines/particle_generator.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "obj_for_engines/renderObj.h"
#include "obj_for_engines/moveObj.h"
#include "utils/random.h"

namespace particle_generator
{
    class Particle : public move_obj::MoveObj, public render_obj::RenderObj
    {
    public:
        Particle(const glm::vec2 &pos, const glm::vec2 &velocity, float endurance,
                 const glm::vec4 &color, const glm::vec2 &size)
            : MoveObj(velocity), RenderObj("particle", "sprite", color),
              Object(pos, size, "Particle"), endurance(endurance) {}

        /// @brief this is for the default constructor
        Particle() : MoveObj(glm::vec2(0.0f)), RenderObj("particle", "sprite", glm::vec4(1.0f)),
                     Object(glm::vec2(0.0f), glm::vec2(0.0f), "Particle") {}
        ~Particle() = default;

        inline void update(float dt)
        {
            // particle will exist for up to one second
            endurance -= 2.5f * dt;
            const auto& temp = getColor();
            if (endurance >= 0.0f)
                // only change the alpha
                setColor(glm::vec4(temp.r, temp.g, temp.b, endurance));
        }

        inline bool isDead() const { return endurance <= 0.0; }

        // set the particle
        void set(const glm::vec2 &master_pos, const glm::vec2 &master_velocity,
                 const glm::vec2 &master_size, const glm::vec4 &master_color, float range);

    private:
        void log_all() override
        {
            log_move();
            log_renderer();
        }
        void detach_all() override
        {
            detach_move();
            detach_renderer();
        }

        /// @brief the time that the particle will exist whose max is 1.0
        float endurance = 0.0f;
    };

    struct ParticleData::ParticleDataPimpl
    {
        const glm::vec2 &master_pos;
        const glm::vec2 &master_velocity;
        const glm::vec2 &master_size;
        const glm::vec4 &master_color;
        bool isSingleUse;
        std::vector<std::unique_ptr<Particle>> particles;
        ParticleDataPimpl(const glm::vec2 &master_pos, const glm::vec2 &master_velocity,
                          const glm::vec2 &master_size, const glm::vec4 &master_color,
                          bool isSingleUse)
            : master_pos(master_pos), master_velocity(master_velocity),
              master_size(master_size), master_color(master_color), isSingleUse(isSingleUse) {}
    };
    namespace
    {
        constexpr unsigned int particles_num = 20;
        constexpr float particle_size = 10.0f;
    }

    ParticleData::ParticleData(const glm::vec2 &master_pos, const glm::vec2 &master_velocity,
                               const glm::vec2 &master_size, const glm::vec4 &master_color,
                               bool isSingleUse)
        : data(std::make_unique<ParticleDataPimpl>(master_pos,
                                                   master_velocity, master_size,
                                                   master_color, isSingleUse))
    {
        float range = isSingleUse ? 25.0f : 5.0f;
        for (unsigned int i = 0; i < particles_num; i++)
        {
            auto particle = std::make_unique<Particle>();
            particle->set(master_pos, master_velocity, master_size, master_color, range);
            data->particles.push_back(std::move(particle));
        }
        for (auto &particle : data->particles)
            particle->log();
    }

    ParticleData::~ParticleData()
    {
        data->particles.clear();
    }

    bool ParticleData::allDead() const
    {
        for (auto &particle : data->particles)
            if (!particle->isDead())
                return false;
        return true;
    }

    void ParticleData::update(float dt)
    {
        for (auto &particle : data->particles)
        {
            if (!particle->isDead())
                particle->update(dt);
            else
            {
                if (data->isSingleUse)
                    particle->detach();
                else // respawn the particle
                {
                    float range = 10.0f;
                    particle->set(data->master_pos, data->master_velocity,
                                  data->master_size, data->master_color, range);
                }
            }
        }
    }

    void ParticleGenerator::update(float dt)
    {
        std::string used_type;
        unsigned int used_id = 0;
        const auto& data = getData();
        for (const auto &[type, id_data] : data)
            for (const auto &[id, particle_data] : id_data)
            {
                particle_data->update(dt);
                if (particle_data->allDead())
                {
                    used_type = type;
                    used_id = id;
                }
            }
        // detach the particles that are out of endurance
        if (used_type.empty() == false)
            detach(used_type, used_id);
    }
    ParticleGenerator::~ParticleGenerator()
    {
    }
    ParticleGenerator::ParticleGenerator()
    {
    }

    void Particle::set(const glm::vec2 &master_pos, const glm::vec2 &master_velocity,
                       const glm::vec2 &master_size, const glm::vec4 &master_color, float range)
    {
        using random::Random;
        glm::vec2 pos;
        pos.x = 2 * Random::instance().randomFloat(range) - range;
        pos.y = 2 * Random::instance().randomFloat(range) - range;

        // standardlize endurence
        this->endurance = (range * sqrt(2.0f) - glm::length(pos)) / range * sqrt(2.0f);

        setPos(master_pos + pos - glm::vec2(particle_size / 2.0f) + master_size / 2.0f);
        setVelocity(pos + master_velocity * 0.1f);
        setColor(glm::vec4(endurance * glm::vec3(10.0f) * glm::vec3(master_color), endurance));
        setSize(glm::vec2(particle_size));
    }
} // namespace particle_generator
