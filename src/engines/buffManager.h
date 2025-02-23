/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-04 18:06:38
 * @LastEditTime: 2025-02-22 21:13:29
 * @FilePath: \breakout_redux\src\engines\buffManager.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <vector>
#include <memory>
#include <string>

#include "obj_for_engines/renderObj.h"
#include "obj_for_engines/moveObj.h"
namespace buff_manager
{
    class BuffManager
    {
    public:
        static BuffManager &instance()
        {
            static BuffManager m_instance;
            return m_instance;
        }

        /// @brief create the buff randonly and the rates is in json file
        void createBuff(const glm::vec2 &master_pos, const glm::vec2 &buffSize);

        /// @brief return the buff type by id and if failed return NULL
        std::string getTypebyId(unsigned int id) const;

    private:
        /// @brief stand by the percentage
        BuffManager();
        ~BuffManager();

        struct BuffData;
        std::unique_ptr<BuffData> data;
    };
} // namespace buff_manager
