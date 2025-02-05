#pragma once
#include <random>
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
    
    /// @brief Generates a random unsigned int between 1 and range
    unsigned int randomInt(unsigned int range)
    {
        std::uniform_int_distribution<unsigned int> distribution(1, range);
        return distribution(generator);
    }

private:
    Random() : generator(rd()){}
    ~Random() = default;
    std::random_device rd;
    std::mt19937 generator;
};