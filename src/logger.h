#pragma once
#include <map>
#include "mString.h"
#include <memory>
/// @brief manages the data from objects
template <typename T>
// TODO 改为指针？或者其他 直接被访问不安全 如何转发或归类 模板
class Logger
{
protected:
    Logger() = default;
    ~Logger()
    {
        data.clear();
    }
    std::map<mString, std::map<unsigned int, std::unique_ptr<T>>> data;

public:
    inline void log(const mString &type, unsigned int id, std::unique_ptr<T> value)
    {
        data[type][id] = std::move(value);
    }
    inline void detach(const mString &type, unsigned int id)
    {
        if (data.empty())
            return;
        data[type].erase(id);
    }
};
