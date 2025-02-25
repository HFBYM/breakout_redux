/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-04 18:06:49
 * @LastEditTime: 2025-02-23 12:40:16
 * @FilePath: \breakout_redux\src\engines\buffManager.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "engines/buffManager.h"

#include <vector>
#include <memory>
#include <map>
#include <string>

#include "utils/random.h"
#include "engines/soundEngine.h"
#include "resource_manage/resource_manager.h"

namespace buff_manager
{
    class Buff : public render_obj::RenderObj, public move_obj::MoveObj
    {
    public:
        Buff(const glm::vec2 &master_pos, const glm::vec2 &size,
            const std::string &type, const std::string &tex, const glm::vec3 &color);
        ~Buff() = default;

        void log_all() override;
        void detach_all() override;

        std::string getType() { return type; }
        unsigned int getId() { return getIdNum(); }

    private:
        std::string type;

        void do_collision(const std::string &message,
            const glm::vec2 &reflect, const glm::vec2 &offset) override;
    };

    struct BuffManager::BuffData
    {
        std::vector<std::unique_ptr<Buff>> buffs;
        std::unique_ptr<move_obj:: MoveObj> buff_range;
    };

    void BuffManager::createBuff(const glm::vec2 &master_pos, const glm::vec2 &size)
    {
        const float chance = m_random::Random::instance().randomFloat(100.0f);
        const auto &data = resource_manager::ResourceManager::instance().getJsonData();
        int chance_sum = 0;
        const auto &m_data = data["resources"]["buff"].get<std::map<std::string,
            resource_manager::ResourceManager::json>>();
        for (const auto &[name, i] : m_data)
        {
            chance_sum += i["chance"].get<int>();
            if (chance < static_cast<float>(chance_sum))
            {
                glm::vec3 color;
                int count = 0;
                for (auto &j : i["color"])
                    color[count++] = j.get<float>();
                this->data->buffs.push_back(std::make_unique<Buff>(master_pos, size, name,
                                    i["texture"].get<std::string>(), color));
                break;
            }
        }
    }

    std::string BuffManager::getTypebyId(unsigned int id) const
    {
        for (const auto &buff : data->buffs)
        {
            if (buff->getId() == id)
                return buff->getType();
        }
        return NULL;
    }

    BuffManager::BuffManager() : data(std::make_unique<BuffData>())
    {
        data->buff_range = std::make_unique<move_obj::MoveObj>("Buff_Range",
            glm::vec2(0.0f, 1500.0f), glm::vec2(1500.0f, 10.0f));
        data->buff_range->log_collision();
    }
    BuffManager::~BuffManager()
    {
        data->buffs.clear();
    }
    Buff::Buff(const glm::vec2 &master_pos, const glm::vec2 &size,
        const std::string &type, const std::string &tex, const glm::vec3 &color)
        : RenderObj(tex, "sprite", glm::vec4(color, 1.0f)), MoveObj(glm::vec2(0.0f, 150.0f)),
        Object(master_pos, size, "Buff"), type(type)
    {
        log_renderer();
        log_move();
        log_collision();
    }

    void Buff::log_all()
    {
        log_renderer();
        log_move();
        log_collision();
    }

    void Buff::detach_all()
    {
        detach_renderer();
        detach_move();
        detach_collision();
    }

    void Buff::do_collision(const std::string &message,
                                const glm::vec2 &reflect, const glm::vec2 &offset)
    {
        using sound_engine::SoundEngine;
        detach_all();
        if (message != "buff_with_range")
            SoundEngine::instance().play_music("POWERUP");
    }
} // namespace buff_manager
