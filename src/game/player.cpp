/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-05 18:27:07
 * @LastEditTime: 2025-02-23 18:58:22
 * @FilePath: \breakout_redux\src\game\player.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "game/player.h"

#include <iostream>
#include <memory>
#include <string>

#include "engines/buffManager.h"
#include "utils/keyval.h"
#include "game/menu.h"
#include "objects/pad.h"
#include "objects/ball.h"
#include "resource_manage/resource_manager.h"

namespace player
{
    using move_obj::MoveObj;
    using pad::Pad;
    using PlayerID = Player::PlayerID;
    using buff_manager::BuffManager;
    using menu::Menu;
    using resource_manager::ResourceManager;

    struct Player::PlayerData
    {
        float pass_through_t = 0.0f;
        float chaos_t = 0.0f;
        float icy_t = 0.0f;
        float stealth_t = 0.0f;
        int score = 0;
        unsigned int screen_width, screen_height;

        std::unique_ptr<pad::Pad> pad;
        std::unique_ptr<ball::Ball> ball;
        PlayerID player_id;
        PlayerData(unsigned int screen_width, unsigned int screen_height, PlayerID player_id)
        : screen_width(screen_width), screen_height(screen_height), player_id(player_id) {}
    };
    namespace
    {
        void initRange(unsigned int screen_width, unsigned int screen_height)
        {
            static std::unique_ptr<std::unique_ptr<move_obj::MoveObj>[]> range =
            std::make_unique<std::unique_ptr<move_obj::MoveObj>[]>(5);
            static bool is_init_range = false;
            if (!is_init_range)
            {
                range[0] = std::make_unique<MoveObj>("Range", glm::vec2(-10.0f, 0.0f),
                                                     glm::vec2(10.0f, screen_height));
                range[1] = std::make_unique<MoveObj>("Range", glm::vec2(screen_width, 0.0f),
                                                     glm::vec2(10.0f, screen_height));
                range[2] = std::make_unique<MoveObj>("Range", glm::vec2(0.0f, -10.0f),
                                                     glm::vec2(screen_width, 10.0f));
                range[3] =
                    std::make_unique<MoveObj>("Range", glm::vec2(0.0f, screen_height),
                                              glm::vec2(screen_width, 10.0f));
                range[4] = std::make_unique<MoveObj>(
                    "Pad_Range", glm::vec2(0.0f, screen_height / 2 - 10.0f),
                    glm::vec2(screen_width, 10.0f));
                for (int i = 0; i < 5; i++)
                    range[i]->log_collision();
            }
            is_init_range = true;
        }
        /// @brief get the color of the player by id
        glm::vec3 getColor(Player::PlayerID player_id)
        {
            switch (player_id)
            {
            case PlayerID::Player_Single:
                return glm::vec3(1.0f);
                break;
            case PlayerID::Player1:
                return glm::vec3(0.5f, 0.5f, 1.0f);
                break;
            case PlayerID::Player2:
                return glm::vec3(1.0f, 1.0f, 0.0f);
                break;
            default:
                return glm::vec3(1.0f);
            }
        }

        glm::vec2 getPos(unsigned int screen_width, unsigned int screen_height,
                                Player:: PlayerID player_id)
        {
            switch (player_id)
            {
            case PlayerID::Player_Single:
                return glm::vec2(screen_width / 2.0f, screen_height);
                break;
            case PlayerID::Player1:
                return glm::vec2(screen_width / 4.0f, screen_height);
                break;
            case PlayerID::Player2:
                return glm::vec2(screen_width / 4.0f * 3.0f, screen_height);
                break;
            default:
                return glm::vec2(screen_width / 2.0f, screen_height);
            }
        }
    } // namespace
    Player::Player(unsigned int screen_width, unsigned int screen_height,
                   PlayerID player_id)
        : Object("Player"),
          data(std::make_unique<PlayerData>(screen_width, screen_height, player_id))
    {
        initRange(screen_width, screen_height);
        add_score(0);

        data->pad = std::make_unique<pad::Pad>(
            player::getPos(screen_width, screen_height, player_id),
        [this](unsigned int id){ this->buff_process(id); }, getColor(player_id));
        data->ball = std::make_unique<ball::Ball>([this](int value)
                                                  { this->add_score(value); }, getColor(player_id));
    }

    Player::~Player() { detach_all(); }

    void Player::log_all()
    {
        data->ball->log();
        data->pad->log();
        log_keyboard();
    }

    void Player::detach_all()
    {
        data->ball->detach();
        data->pad->detach();
        detach_keyboard();
    }

    void Player::update(float dt)
    {
        data->ball->setPos(data->pad->getPos(), data->pad->getSize(),
            data->screen_width, data->screen_height);
        if (data->pass_through_t > 0.0f)
        {
            data->pass_through_t -= dt;
            if (data->pass_through_t <= 0.0f)
            {
                data->ball->setThrough(false);
                data->ball->resetColor();
            }
        }
        if (data->chaos_t > 0.0f)
        {
            data->chaos_t -= dt;
            if (data->chaos_t <= 0.0f)
                data->pad->setChaos(false);
        }
        if (data->icy_t > 0.0f)
        {
            data->icy_t -= dt;
            if (data->icy_t <= 0.0f)
                data->pad->setIcy(false);
        }
        if (data->stealth_t > 0.0f)
        {
            data->stealth_t -= dt;
            if (data->stealth_t <= 0.0f)
                data->ball->setStealth(false);
        }
    }

    void Player::processInput(int key, int action)
    {
        if (data->player_id == PlayerID::Player1 || data->player_id == PlayerID::Player_Single)
        {
            if (action == GLFW_PRESS)
            {
                switch (key)
                {
                case GLFW_KEY_A:
                    data->pad->processInput(Pad::Key::LEFT, true);
                    break;
                case GLFW_KEY_D:
                    data->pad->processInput(Pad::Key::RIGHT, true);
                    break;
                case GLFW_KEY_W:
                    data->pad->processInput(Pad::Key::UP, true);
                    break;
                case GLFW_KEY_S:
                    data->pad->processInput(Pad::Key::DOWN, true);
                    break;
                default:
                    break;
                }
                if (key == GLFW_KEY_SPACE)
                    data->ball->processInput(key, true);
            }
            else if (action == GLFW_RELEASE)
            {
                switch (key)
                {
                case GLFW_KEY_A:
                    data->pad->processInput(Pad::Key::LEFT, false);
                    break;
                case GLFW_KEY_D:
                    data->pad->processInput(Pad::Key::RIGHT, false);
                    break;
                case GLFW_KEY_W:
                    data->pad->processInput(Pad::Key::UP, false);
                    break;
                case GLFW_KEY_S:
                    data->pad->processInput(Pad::Key::DOWN, false);
                    break;
                default:
                    break;
                }
            }
        }
        else if (data->player_id == PlayerID::Player2)
        {
            if (action == GLFW_PRESS)
            {
                switch (key)
                {
                case GLFW_KEY_LEFT:
                    data->pad->processInput(Pad::Key::LEFT, true);
                    break;
                case GLFW_KEY_RIGHT:
                    data->pad->processInput(Pad::Key::RIGHT, true);
                    break;
                case GLFW_KEY_UP:
                    data->pad->processInput(Pad::Key::UP, true);
                    break;
                case GLFW_KEY_DOWN:
                    data->pad->processInput(Pad::Key::DOWN, true);
                    break;
                default:
                    break;
                }
                if (key == GLFW_KEY_RIGHT_ALT)
                    data->ball->processInput(key, true);
            }
            else if (action == GLFW_RELEASE)
            {
                switch (key)
                {
                case GLFW_KEY_LEFT:
                    data->pad->processInput(Pad::Key::LEFT, false);
                    break;
                case GLFW_KEY_RIGHT:
                    data->pad->processInput(Pad::Key::RIGHT, false);
                    break;
                case GLFW_KEY_UP:
                    data->pad->processInput(Pad::Key::UP, false);
                    break;
                case GLFW_KEY_DOWN:
                    data->pad->processInput(Pad::Key::DOWN, false);
                    break;
                default:
                    break;
                }
            }
        }
    }

    void Player::buff_process(unsigned int id)
    {
        std::string type = BuffManager::instance().getTypebyId(id);
        const auto &data = ResourceManager::instance().getJsonData();
        if (type == "SPEED")
            this->data->pad->speedup(false);
        else if (type == "STICKY")
            this->data->ball->setSticked(true);
        else if (type == "PASS_THROUGH")
        {
            this->data->ball->setThrough(true);
            this->data->ball->setColor(glm::vec3(1.0f, 0.6f, 0.3f));
            this->data->pass_through_t = data["resources"]["buff"][type]["endurence"].get<float>();
        }
        else if (type == "PAD_SIZE_INCREASE")
            this->data->pad->sizeIncrease(false);
        else if (type == "CHAOS")
        {
            this->data->pad->setChaos(true);
            this->data->chaos_t = data["resources"]["buff"][type]["endurence"].get<float>();
        }
        else if (type == "ICY")
        {
            this->data->pad->setIcy(true);
            this->data->icy_t = data["resources"]["buff"][type]["endurence"].get<float>();
        }
        else if (type == "CLEAN")
        {
            this->data->pad->setChaos(false);
            this->data->pad->setIcy(false);
            this->data->pad->speedup(true);
            this->data->pad->sizeIncrease(true);
            this->data->ball->setThrough(false);
            this->data->ball->resetColor();
            this->data->ball->setStealth(false);
        }
        else if (type == "STEALTH")
        {
            this->data->ball->setStealth(true);
            this->data->stealth_t = data["resources"]["buff"][type]["endurence"].get<float>();
        }
        else
            throw "ERROR::BUFF: undefined type " + type;
    }

    void Player::add_score(int value)
    {
        data->score += value;
        if (data->player_id == PlayerID::Player1)
        {
            Menu::setCursorPos(0, 1);
            std::cout << "\033[K";
            Menu::setCursorPos(0, 1);
            std::cout << "Player1 Score: " << data->score << std::endl
                      << std::endl;
        }
        else if (data->player_id == PlayerID::Player2)
        {
            Menu::setCursorPos(0, 2);
            std::cout << "\033[K";
            Menu::setCursorPos(0, 2);
            std::cout << "Player2 Score: " << data->score << std::endl;
        }
        else
            return;
    }
} // namespace player
