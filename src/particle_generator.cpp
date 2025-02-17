#include "particle_generator.h"
#include <iostream>
#include"random.h"

static const unsigned int particles_num = 20;
static const float particle_size = 10.0f;

ParticleData::ParticleData(const glm::vec2 &master_pos, const glm::vec2 &master_velocity, const glm::vec2 &master_size, const glm::vec4 &master_color, bool isSingleUse)
    : master_pos(master_pos), master_velocity(master_velocity), isSingleUse(isSingleUse), master_size(master_size), master_color(master_color)
{
    float range = isSingleUse ? 25.0f : 5.0f;
    for (unsigned int i = 0; i < particles_num; i++)
    {
        auto particle = std::make_unique<Particle>();
        particle->set(master_pos, master_velocity, master_size, master_color, range);
        particles.push_back(std::move(particle));
    }
    for (auto &particle : particles)
        particle->log_all();
}

ParticleData::~ParticleData()
{
    particles.clear();
}

bool ParticleData::allDead() const
{
    for (auto &particle : particles)
        if (!particle->isDead())
            return false;
    return true;
}

void ParticleData::update(float dt)
{
    for (auto &particle : particles)
    {
        if (!particle->isDead())
            particle->update(dt);
        else
        {
            if (isSingleUse)
                particle->detach_all();
            else // respawn the particle
            {
                float range = 10.0f;
                particle->set(master_pos, master_velocity, master_size, master_color, range);
            }
        }
    }
}

void ParticleGenerator::update(float dt)
{
    std::string used_type;
    unsigned int used_id = 0;
    for (auto &[type, id_data] : data)
        for (auto &[id, particle_data] : id_data)
        {
            particle_data->update(dt);
            if (particle_data->allDead())
            {
                used_type = type;
                used_id = id;
            }
        }
    // detach the particles that are out of endurance
    if(used_type.empty() == false)
        detach(used_type, used_id);
}
ParticleGenerator::~ParticleGenerator()
{
}
ParticleGenerator::ParticleGenerator()
{
}

void Particle::set(const glm::vec2 &master_pos, const glm::vec2 &master_velocity, const glm::vec2 &master_size, const glm::vec4 &master_color, float range)
{
    glm::vec2 pos;
    pos.x = 2 * Random::instance().randomFloat(range) - range;
    pos.y = 2 * Random::instance().randomFloat(range) - range;

    // standardlize endurence
    this->endurance = (range * sqrt(2.0f) - glm::length(pos)) / range * sqrt(2.0f);
    
    this->pos = master_pos + pos - glm::vec2(particle_size / 2.0f) + master_size / 2.0f;
    this->velocity = pos + master_velocity * 0.1f;
    this->color = glm::vec4(endurance * glm::vec3(10.0f) * glm::vec3(master_color), endurance);
    this->size = glm::vec2(particle_size);
}
