#include "buffManager.h"
#include "random.h"
#include "soundEngine.h"
#include "resource_manager.h"
#include <iostream>

void BuffManager::createBuff(const glm::vec2 &master_pos, const glm::vec2 &size)
{
    float chance = Random::instance().randomFloat(100.0f);
    const auto &data = ResourceManager::instance().getJsonData();
    int chance_sum = 0;
    auto m_data = data["resources"]["buff"].get<std::map<std::string, ResourceManager::json>>();
    for (auto &[name, i] : m_data)
    {
        chance_sum += i["chance"].get<int>();
        if (chance < static_cast<float>(chance_sum))
        {
            glm::vec3 color;
            int count = 0;
            for (auto &j : i["color"])
                color[count++] = j.get<float>();
            buffs.push_back(std::make_unique<Buff>(master_pos, size, name, i["texture"].get<std::string>(), color));
            break;
        }
    }
}

std::string BuffManager::getTypebyId(unsigned int id)
{
    for (auto &buff : buffs)
    {
        if (buff->getId() == id)
            return buff->getType();
    }
    return NULL;
}

BuffManager::BuffManager()
{
    buff_range = std::make_unique<MoveObj>("Buff_Range", glm::vec2(0.0f, 1500.0f), glm::vec2(1500.0f, 10.0f));
    buff_range->log_collision();
}
BuffManager::~BuffManager()
{
    buffs.clear();
}
BuffManager::Buff::Buff(const glm::vec2 &master_pos, const glm::vec2 &size, const std::string &type, const std::string &tex, const glm::vec3 &color)
    : RenderObj(tex, "sprite", glm::vec4(color, 1.0f)), MoveObj(glm::vec2(0.0f, 150.0f)), Object(master_pos, size, "Buff"), type(type)
{
    log_all();
}

void BuffManager::Buff::log_all()
{

    log_renderer();
    log_move();
    log_collision();
}

void BuffManager::Buff::detach_all()
{
    detach_renderer();
    detach_move();
    detach_collision();
}

void BuffManager::Buff::do_collision(const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
    detach_all();
    if (message != "buff_with_range")
        SoundEngine::instance().play_music("POWERUP");
}
