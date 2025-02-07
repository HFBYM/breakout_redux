#include "buffManager.h"
#include "random.h"
#include "soundEngine.h"
#include <iostream>

//TODO 更好的等概率生成
void BuffManager::createBuff(const glm::vec2 &master_pos, const glm::vec2 &size)
{
    float chance = Random::instance().randomFloat(100.0f);
    if (chance < static_cast<float>(BuffRate::SPEED))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::SPEED));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::SPEED))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::STICKY));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::PASS_THROUGH) + static_cast<float>(BuffRate::SPEED))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::PASS_THROUGH));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::PASS_THROUGH) + static_cast<float>(BuffRate::PAD_SIZE_INCREASE) + static_cast<float>(BuffRate::SPEED))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::PAD_SIZE_INCREASE));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::PASS_THROUGH) + static_cast<float>(BuffRate::PAD_SIZE_INCREASE) + static_cast<float>(BuffRate::CHAOS) + static_cast<float>(BuffRate::SPEED))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::CHAOS));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::PASS_THROUGH) + static_cast<float>(BuffRate::PAD_SIZE_INCREASE) + static_cast<float>(BuffRate::CHAOS) + static_cast<float>(BuffRate::SPEED) + static_cast<float>(BuffRate::ICY))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::ICY));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::PASS_THROUGH) + static_cast<float>(BuffRate::PAD_SIZE_INCREASE) + static_cast<float>(BuffRate::CHAOS) + static_cast<float>(BuffRate::SPEED) + static_cast<float>(BuffRate::ICY) + static_cast<float>(BuffRate::CLEAN))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::CLEAN));
    else if (chance < static_cast<float>(BuffRate::STICKY) + static_cast<float>(BuffRate::PASS_THROUGH) + static_cast<float>(BuffRate::PAD_SIZE_INCREASE) + static_cast<float>(BuffRate::CHAOS) + static_cast<float>(BuffRate::SPEED) + static_cast<float>(BuffRate::ICY) + static_cast<float>(BuffRate::CLEAN) + static_cast<float>(BuffRate::STEALTH))
        buffs.push_back(std::make_unique<Buff>(master_pos, size, BuffType::STEALTH));
    else
        return;
}

BuffManager::BuffType BuffManager::getTypebyId(unsigned int id)
{
    for (auto &buff : buffs)
    {
        if (buff->getId() == id)
            return buff->getType();
    }
    return BuffManager::BuffType::NONE;
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
BuffManager::Buff::Buff(const glm::vec2 &master_pos, const glm::vec2 &size, BuffType type)
    : RenderObj(getTex(type), "sprite", glm::vec4(getColor(type), 1.0f)), MoveObj(glm::vec2(0.0f, 150.0f)), Object(master_pos, size, "Buff"), type(type)
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

mString BuffManager::Buff::getTex(BuffType type)
{
    switch (type)
    {
    case BuffType::SPEED:
        return "tex_speed";
        break;
    case BuffType::STICKY:
        return "tex_sticky";
        break;
    case BuffType::PASS_THROUGH:
        return "tex_pass";
        break;
    case BuffType::PAD_SIZE_INCREASE:
        return "tex_size";
        break;
    case BuffType::CHAOS:
        return "tex_chaos";
        break;
    case BuffType::ICY:
        return "tex_chaos";
        break;
    case BuffType::CLEAN:
        return "tex_confuse";
        break;
    case BuffType::STEALTH:
        return "tex_speed";
        break;
    default:
        return NULL;
        break;
    }
}

glm::vec3 BuffManager::Buff::getColor(BuffType type)
{
    switch (type)
    {
    case BuffType::SPEED:
        return glm::vec3(0.5f, 0.5f, 1.0f);
        break;
    case BuffType::STICKY:
        return glm::vec3(1.00, 0.41, 0.71);
        break;
    case BuffType::PASS_THROUGH:
        return glm::vec3(0.5f, 1.0f, 0.5f);
        break;
    case BuffType::PAD_SIZE_INCREASE:
        return glm::vec3(1.00, 0.65, 0.00);
        break;
    case BuffType::CHAOS:
        return glm::vec3(0.9f, 0.25f, 0.25f);
        break;
    case BuffType::ICY:
        return glm::vec3(0.0f, 0.27f, 1.0f);
        break;
    case BuffType::CLEAN:
        return glm::vec3(0.00, 1.00, 1.00);
        break;
    case BuffType::STEALTH:
        return glm::vec3(0.75, 0.75, 0.75);
        break;
    default:
        return glm::vec3(1.0f, 1.0f, 1.0f);
        break;
    }
}
void BuffManager::Buff::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
    detach_all();
    if (message != "buff_with_range")
        SoundEngine::instance().play_music(SoundEngine::Song::POWERUP);
}
