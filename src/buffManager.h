#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include <vector>
class BuffManager
{
public:
    enum class BuffType
    {
        NONE,
        SPEED,
        STICKY,
        PASS_THROUGH,
        PAD_SIZE_INCREASE,
        CHAOS,
        ICY,
        CLEAN,
        STEALTH
    };

    /// @brief the buff endure time by second
    enum class BuffTime
    {
        PASS_THROUGH = 10,
        CHAOS = 10,
        ICY = 10,
        STEALTH = 10
    };

    class Buff : public RenderObj, public MoveObj
    {
    public:
        Buff(const glm::vec2 &master_pos, const glm::vec2 &size, BuffType type);
        ~Buff() { detach_all(); }

        void log_all() override;
        void detach_all() override;

        BuffType getType() { return type; }
        unsigned int getId() { return id_num; }

    private:
        BuffType type = BuffType::NONE;

        static mString getTex(BuffType type);
        static glm::vec3 getColor(BuffType type);
        
        void do_collision(const mString& message, const glm::vec2& reflect, const glm::vec2& offset) override;
    };

    static BuffManager &instance()
    {
        static BuffManager m_instance;
        return m_instance;
    }

    /// @brief create the buff randonly
    void createBuff(const glm::vec2 &master_pos, const glm::vec2 &buffSize);

    /// @brief return the buff type by id
    BuffManager::BuffType getTypebyId(unsigned int id);

private:
    /// @brief stand by the percentage
    enum class BuffRate
    {
        SPEED = 10,
        STICKY = 10,
        PASS_THROUGH = 10,
        PAD_SIZE_INCREASE = 10,
        CHAOS = 10,
        ICY = 10,
        CLEAN = 10,
        STEALTH = 10
    };
    BuffManager();
    ~BuffManager();
    std::vector<std::unique_ptr<Buff>> buffs;
    std::unique_ptr<MoveObj> buff_range;
};