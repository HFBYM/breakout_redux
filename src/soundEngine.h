#pragma once
#include <include/irrKlang.h>
//TODO 动态库问题
class SoundEngine
{
public:
    enum Song{
        BGM = 0,
        SOLID,
        BLEEPMP3,
        BLEEPWAV,
        POWERUP
    };
    static SoundEngine &instance()
    {
        static SoundEngine instance;
        return instance;
    }
    void play_music(Song song);

private:
    SoundEngine();
    ~SoundEngine();
    irrklang::ISoundEngine* sound_engine = nullptr;
};