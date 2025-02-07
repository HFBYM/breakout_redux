#include "player.h"
#include "keyval.h"
#include "buffManager.h"
#include <iostream>

std::unique_ptr<std::unique_ptr<MoveObj>[]> Player::range(std::make_unique<std::unique_ptr<MoveObj>[]>(5));

Player::Player(unsigned int screen_width, unsigned int screen_height, PlayerID player_id)
    : pad(std::make_unique<Pad>(getPos(screen_width, screen_height, player_id), [this](unsigned int id)
                                { this->buff_process(id); }, getColor(player_id))),
      ball(std::make_unique<Ball>(getColor(player_id))), Object("Player"), player_id(player_id)
{
    static bool is_init_range = false;
    if (!is_init_range)
    {
        range[0] = std::make_unique<MoveObj>("Range", glm::vec2(-10.0f, 0.0f), glm::vec2(10.0f, screen_height));
        range[1] = std::make_unique<MoveObj>("Range", glm::vec2(screen_width, 0.0f), glm::vec2(10.0f, screen_height));
        range[2] = std::make_unique<MoveObj>("Range", glm::vec2(0.0f, -10.0f), glm::vec2(screen_width, 10.0f));
        range[3] = std::make_unique<MoveObj>("Range", glm::vec2(0.0f, screen_height), glm::vec2(screen_width, 10.0f));
        range[4] = std::make_unique<MoveObj>("Pad_Range", glm::vec2(0.0f, screen_height / 2 - 10.0f), glm::vec2(screen_width, 10.0f));
        for (int i = 0; i < 5; i++)
            range[i]->log_collision();
    }
    is_init_range = true;
}

Player::~Player()
{
    detach_all();
}

void Player::log_all()
{
    ball->log_all();
    pad->log_all();
    log_keyboard();
}

void Player::detach_all()
{
    ball->detach_all();
    pad->detach_all();
    detach_keyboard();
}

void Player::update(float dt)
{
    ball->setPos(pad->getPos(), pad->getSize());
    if (pass_through_t > 0.0f)
    {
        pass_through_t -= dt;
        if (pass_through_t <= 0.0f)
        {
            ball->setThrough(false);
            ball->resetColor();
        }
    }
    if (chaos_t > 0.0f)
    {
        chaos_t -= dt;
        if (chaos_t <= 0.0f)
            pad->setChaos(false);
    }
    if (icy_t > 0.0f)
    {
        icy_t -= dt;
        if (icy_t <= 0.0f)
            pad->setIcy(false);
    }
    if (stealth_t > 0.0f)
    {
        stealth_t -= dt;
        if (stealth_t <= 0.0f)
            ball->setStealth(false);
    }
}

void Player::processInput(int key, int action)
{
    if (player_id == PlayerID::Player1 || player_id == PlayerID::Player_Single)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_A:
                pad->processInput(Pad::Key::LEFT, true);
                break;
            case GLFW_KEY_D:
                pad->processInput(Pad::Key::RIGHT, true);
                break;
            case GLFW_KEY_W:
                pad->processInput(Pad::Key::UP, true);
                break;
            case GLFW_KEY_S:
                pad->processInput(Pad::Key::DOWN, true);
                break;
            default:
                break;
            }
            if (key == GLFW_KEY_SPACE)
                ball->processInput(key, true);
        }
        else if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_A:
                pad->processInput(Pad::Key::LEFT, false);
                break;
            case GLFW_KEY_D:
                pad->processInput(Pad::Key::RIGHT, false);
                break;
            case GLFW_KEY_W:
                pad->processInput(Pad::Key::UP, false);
                break;
            case GLFW_KEY_S:
                pad->processInput(Pad::Key::DOWN, false);
                break;
            default:
                break;
            }
            if (key == GLFW_KEY_SPACE)
                ball->processInput(key, false);
        }
    }
    else if (player_id == PlayerID::Player2)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_LEFT:
                pad->processInput(Pad::Key::LEFT, true);
                break;
            case GLFW_KEY_RIGHT:
                pad->processInput(Pad::Key::RIGHT, true);
                break;
            case GLFW_KEY_UP:
                pad->processInput(Pad::Key::UP, true);
                break;
            case GLFW_KEY_DOWN:
                pad->processInput(Pad::Key::DOWN, true);
                break;
            default:
                break;
            }
            if (key == GLFW_KEY_RIGHT_ALT)
                ball->processInput(key, true);
        }
        else if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_LEFT:
                pad->processInput(Pad::Key::LEFT, false);
                break;
            case GLFW_KEY_RIGHT:
                pad->processInput(Pad::Key::RIGHT, false);
                break;
            case GLFW_KEY_UP:
                pad->processInput(Pad::Key::UP, false);
                break;
            case GLFW_KEY_DOWN:
                pad->processInput(Pad::Key::DOWN, false);
                break;
            default:
                break;
            }
            if (key == GLFW_KEY_RIGHT_ALT)
                ball->processInput(key, false);
        }
    }
}

// TODO BUFF美术效果
void Player::buff_process(unsigned int id)
{
    switch (BuffManager::instance().getTypebyId(id))
    {
    case BuffManager::BuffType::SPEED:
        pad->speedup();
        break;
    case BuffManager::BuffType::STICKY:
        ball->setSticked(true);
        break;
    case BuffManager::BuffType::PASS_THROUGH:
        ball->setThrough(true);
        ball->setColor(glm::vec3(1.0f, 0.6f, 0.3f));
        pass_through_t = static_cast<float>(BuffManager::BuffTime::PASS_THROUGH);
        break;
    case BuffManager::BuffType::PAD_SIZE_INCREASE:
        pad->sizeIncrease();
        break;
    case BuffManager::BuffType::CHAOS:
        pad->setChaos(true);
        chaos_t = static_cast<float>(BuffManager::BuffTime::CHAOS);
        break;
    case BuffManager::BuffType::ICY:
        pad->setIcy(true);
        icy_t = static_cast<float>(BuffManager::BuffTime::ICY);
        break;
    case BuffManager::BuffType::CLEAN:
        pad->setChaos(false);
        pad->setIcy(false);
        pad->speedup(true);
        pad->sizeIncrease(true);
        ball->setThrough(false);
        ball->resetColor();
        ball->setStealth(false);
        break;
    case BuffManager::BuffType::STEALTH:
        ball->setStealth(true);
        stealth_t = static_cast<float>(BuffManager::BuffTime::STEALTH);
        break;
    default:
        break;
    }
}

glm::vec3 Player::getColor(PlayerID player_id)
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

glm::vec2 Player::getPos(unsigned int screen_width, unsigned int screen_height, PlayerID player_id)
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
