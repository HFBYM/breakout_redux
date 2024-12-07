#pragma once
#include <map>
#include "mString.h"
/// @brief manages the data from objects
template <typename T>
class Logger
{
private:
    std::map<mString, std::map<unsigned int, T *>> &data;

public:
    /// @brief let the logger take control of the data
    Logger(std::map<mString, std::map<unsigned int, T *>> &data) : data(data) {}
    ~Logger() = default;

    inline void log(const mString& type, unsigned int id, T value){data[type][id] = new T(value);}
    inline void detach(const mString& type, unsigned int id)
    {
        if(data[type][id]) 
            delete data[type][id];
        data[type][id] = nullptr;
        data[type].erase(id);
    }
    inline void clear()
    {
        for(auto& i : data) 
        { 
            for(auto& j : i.second) 
                if(j.second)
                {
                    delete j.second;
                    j.second = nullptr;
                }
            i.second.clear();
        }
        data.clear();
    }
};
