/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:02:20
 * @FilePath: \breakout_redux\src\resource_manage\logger.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include "utils/pch.h"
namespace logger
{
    /// @brief manage the data from objects
    template <typename T>
    class Logger
    {
    private:
        using Data = std::map<std::string, std::map<unsigned int, std::unique_ptr<T>>>;

    public:
        inline void log(const std::string &type, unsigned int id, std::unique_ptr<T> value)
        {
            data[type][id] = std::move(value);
        }
        inline void detach(const std::string &type, unsigned int id)
        {
            if (data.empty())
                return;
            data[type].erase(id);
        }
        inline const Data& getData() const
        {
            return data;
        }

    protected:
        Logger() = default;
        virtual ~Logger()
        {
            // if doesn't clear, some will access invalid data and get errors
            data.clear();
        }

    private:
        // just using the ptr
        Data data;
    };
} // namespace logger
