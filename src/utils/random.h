/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-04 18:38:32
 * @LastEditTime: 2025-02-23 11:07:16
 * @FilePath: \breakout_redux\src\utils\random.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <random>
namespace m_random
{
    class Random
    {
    public:
        static Random &instance()
        {
            static Random m_instance;
            return m_instance;
        }

        /// @brief Generates a random float between 0 and range
        float randomFloat(float range)
        {
            std::uniform_real_distribution<float> distribution(0.0f, range);
            return distribution(generator);
        }
        /// @brief Generates a random unsigned int between 0 and range
        unsigned int randomInt(unsigned int range)
        {
            std::uniform_int_distribution<unsigned int> distribution(0, range);
            return distribution(generator);
        }

    private:
        Random() : generator(rd()) {}
        ~Random() = default;
        std::random_device rd;
        std::mt19937 generator;
    };
} // namespace m_random
