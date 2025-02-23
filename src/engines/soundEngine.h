/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-04 15:12:10
 * @LastEditTime: 2025-02-23 09:17:51
 * @FilePath: \breakout_redux\src\engines\soundEngine.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <include/irrKlang.h>
#include <string>
namespace sound_engine
{
    class SoundEngine
    {
    public:
        static SoundEngine &instance()
        {
            static SoundEngine instance;
            return instance;
        }
        void play_music(const std::string song) const;

    private:
        SoundEngine();
        ~SoundEngine();
        irrklang::ISoundEngine *sound_engine = nullptr;
    };
} // namespace sound_engine
