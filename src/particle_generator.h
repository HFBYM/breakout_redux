#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include "logger.h"
#include <vector>
#include <memory>

class Particle : public MoveObj, public RenderObj
{
public:
    Particle(const glm::vec2 &pos, const glm::vec2 &velocity, float endurance, const glm::vec4 &color, const glm::vec2 &size) : MoveObj(velocity), RenderObj("particle", "sprite", color), Object(pos, size, "Particle"), endurance(endurance) {}
    Particle(): MoveObj(), RenderObj("particle", "sprite", glm::vec4(1.0f)), Object(glm::vec2(0.0f), glm::vec2(0.0f), "Particle") {}
    ~Particle() = default;

    inline void log_all() override
    {
        log_move();
        log_renderer();
    }
    inline void detach_all() override
    {
        detach_move();
        detach_renderer();
    }

    inline void setPos(const glm::vec2 &pos) { this->pos = pos; }
    inline void setVelosity(const glm::vec2 &velocity) { this->velocity = velocity; }
    inline void update(float dt)
    {
        // particle will exist for up to one second
        endurance -= 2.5f * dt;
        if (endurance >= 0.0f)
            // only change the alpha
            color.w = endurance;
    }
    inline bool isDead() const { return endurance <= 0.0; }

    // set the particle
    void set(const glm::vec2 &master_pos, const glm::vec2 &master_velocity, const glm::vec2 &master_size, const glm::vec4 &master_color, float range);

private:
    /// @brief the time that the particle will exist whose max is 1.0
    float endurance = 0.0f;
};

class ParticleData
{
private:
    const glm::vec2 &master_pos;
    const glm::vec2 &master_velocity;
    const glm::vec2 &master_size;
    const glm::vec4 &master_color;
    bool isSingleUse;
    std::vector<std::unique_ptr<Particle>> particles;

public:
    /// @brief it will generate particles when logging
    /// @param master_pos the pos of the master object
    /// @param master_velocity  the velocity of the master object and if it dosen't exist, it should be set to zero
    /// @param isSingleUse  if true, the particles will not be regenerated
    ParticleData(const glm::vec2 &master_pos, const glm::vec2 &master_velocity, const glm::vec2 &master_size, const glm::vec4 &master_color, bool isSingleUse = true);
    ~ParticleData();

    bool allDead() const;
    void update(float dt);
};

// trigger the generator by logging data
class ParticleGenerator : public Logger<ParticleData>
{
public:
    using Data = ParticleData;
    static inline ParticleGenerator &instance()
    {
        static ParticleGenerator instance;
        return instance;
    }

    /// @brief update particles and remove them if they are out of endurance
    /// @param dt delta time from last update
    void update(float dt);

private:
    ParticleGenerator();
    ~ParticleGenerator();
};