/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-04 15:12:01
 * @LastEditTime: 2025-02-23 09:50:27
 * @FilePath: \breakout_redux\src\engines\soundEngine.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "engines/soundEngine.h"

#include<map>
#include<string>

#include<json.hpp>
#include "utils/debug.h"
#include "resource_manage/resource_manager.h"
#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif
namespace sound_engine
{
    SoundEngine::~SoundEngine()
    {
        if (sound_engine)
            delete sound_engine;
    }
    void SoundEngine::play_music(const std::string song) const
    {
        using resource_manager::ResourceManager;
        const auto &data = ResourceManager::instance().getJsonData();
        const std::string project_dir(PROJECT_DIR "/");
        for (const auto &[name, i] :
            data["resources"]["music"].get<std::map<std::string, ResourceManager::json>>())
            if (name == song)
            {
                const auto path = project_dir + i["path"].get<std::string>();
                sound_engine->play2D(path.c_str(), i["isRepeated"].get<bool>());
                return;
            }
        MDEBUG();
    }
    SoundEngine::SoundEngine()
    {
        sound_engine = irrklang::createIrrKlangDevice();
    }
} // namespace sound_engine
