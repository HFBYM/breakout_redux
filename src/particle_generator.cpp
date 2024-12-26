#include "particle_generator.h"
#include <random>
#include <iostream>
#include"check.h"

static bool isClear = false;

static std::map<mString, std::map<unsigned int, ParticleGenerator::ParticleData *>> particle_data;
Logger<ParticleGenerator::ParticleData> ParticleGenerator::logger(particle_data);

static unsigned int particles_num = 20;
static float particle_size = 10.0f;

/// @brief Generates a random float between 0 and range
static float randomFloat(float range)
{
    static std::random_device seed;
    static std::mt19937 generator(seed());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return range * distribution(generator);
}

ParticleGenerator::ParticleData::ParticleData(const glm::vec2 &master_pos, const glm::vec2 &master_velocity, bool isSingleUse)
    : master_pos(master_pos), master_velocity(master_velocity), isSingleUse(isSingleUse)
{
    float range = 5.0f;
    glm::vec2 velocity;
    glm::vec2 pos;
    float endurence;
    for (unsigned int i = 0; i < particles_num; i++)
    {
        pos.x = randomFloat(-range);
        pos.y = randomFloat(range);
        velocity = master_velocity * 0.1f;
        // standardlize endurence
        endurence = (range * sqrt(2.0f) - glm::length(pos)) / range * sqrt(2.0f);
        particles.push_back(new Particle(master_pos + pos - glm::vec2(particle_size / 2.0f), velocity, endurence, endurence * glm::vec3(1.0f), glm::vec2(particle_size)));
    }
    for(auto& particle: particles)
        particle->log_all();
}

ParticleGenerator::ParticleData::~ParticleData()
{
    for(auto& particle: particles)
    {
        if(particle)
        {
            particle->detach_all();
            delete particle;
        }
    }
    particles.clear();
}

void ParticleGenerator::clear()
{
}
