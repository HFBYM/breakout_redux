#pragma once
#include <include/irrKlang.h>
#include <string>
class SoundEngine
{
public:
    static SoundEngine &instance()
    {
        static SoundEngine instance;
        return instance;
    }
    void play_music(std::string song);

private:
    SoundEngine();
    ~SoundEngine();
    irrklang::ISoundEngine *sound_engine = nullptr;
};