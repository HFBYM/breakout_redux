#pragma once
#include <map>
#include "mString.h"
#include <memory>
/// @brief manages the data from objects
template <typename T>
class Logger
{
protected:
    Logger() = default;
    ~Logger()
    {
        // if doesn't clear, some will access invalid data and get errors
        data.clear();
    }
    // just using the ptr
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
