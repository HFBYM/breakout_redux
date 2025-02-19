#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include <vector>
#include<memory>
class BuffManager
{
public:
    class Buff : public RenderObj, public MoveObj
    {
    public:
        Buff(const glm::vec2 &master_pos, const glm::vec2 &size, const std::string& type, const std::string& tex, const glm::vec3& color);
        ~Buff() { detach_all(); }

        void log_all() override;
        void detach_all() override;

        std::string getType() { return type; }
        unsigned int getId() { return id_num; }

    private:
        std::string type;
        
        void do_collision(const std::string& message, const glm::vec2& reflect, const glm::vec2& offset) override;
    };

    static BuffManager &instance()
    {
        static BuffManager m_instance;
        return m_instance;
    }

    /// @brief create the buff randonly
    void createBuff(const glm::vec2 &master_pos, const glm::vec2 &buffSize);

    /// @brief return the buff type by id
    std::string getTypebyId(unsigned int id);

private:
    /// @brief stand by the percentage
    BuffManager();
    ~BuffManager();
    std::vector<std::unique_ptr<Buff>> buffs;
    std::unique_ptr<MoveObj> buff_range;
};