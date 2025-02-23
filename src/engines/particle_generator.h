/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 12:54:46
 * @FilePath: \breakout_redux\src\engines\particle_generator.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <memory>
#include<glm.hpp>
#include "resource_manage/logger.h"

namespace particle_generator
{
    class ParticleData
    {
    private:
        struct ParticleDataPimpl;
        std::unique_ptr<ParticleDataPimpl> data;

    public:
        /// @brief it will generate particles when logging
        /// @param master_pos the pos of the master object
        /// @param master_velocity  if it dosen't exist, it should be set to zero
        /// @param isSingleUse  if true, the particles will not be regenerated
        ParticleData(const glm::vec2 &master_pos, const glm::vec2 &master_velocity,
            const glm::vec2 &master_size, const glm::vec4 &master_color, bool isSingleUse);
        ~ParticleData();

        bool allDead() const;
        void update(float dt);
    };

    // trigger the generator by logging data
    class ParticleGenerator : public logger::Logger<ParticleData>
    {
    public:
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
} // namespace particle_generator
