#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include "logger.h"
#include <vector>
class ParticleGenerator
{
private:
    class Particle : public MoveObj, public RenderObj
    {
    public:
        Particle(const glm::vec2 &pos, const glm::vec2 &velocity, float endurance, const glm::vec3 &color, const glm::vec2 &size) : MoveObj(velocity), RenderObj("particle", "sprite", color), Object(pos, size, "Particle"), endurance(endurance) {}
        ~Particle() = default;

        inline void log_all() override
        {
            log_collision();
            log_renderer();
        }
        inline void detach_all() override
        {
            detach_collision();
            detach_renderer();
        }

        inline void setPos(const glm::vec2 &pos) { this->pos = pos; }
        inline void setVelosity(const glm::vec2 &velocity) { this->velocity = velocity; }

    private:
        /// @brief the time that the particle will exist whose max is 1.0
        float endurance;
    };

public:
    struct ParticleData
    {
        /// @brief the center of the master object
        const glm::vec2 &master_pos;
        const glm::vec2 &master_velocity;
        bool isSingleUse;
        std::vector<Particle *> particles;
        ParticleData(const glm::vec2 &master_pos, const glm::vec2 &master_velocity, bool isSingleUse = true);
        ~ParticleData();
    };

    static Logger<ParticleData> logger;
        /// @brief it can't be cleared twice
    static void clear();


private:
    ParticleGenerator() = delete;
    ~ParticleGenerator() = delete;
};