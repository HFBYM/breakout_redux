#pragma once
#include <include/irrKlang.h>
class SoundEngine
{
public:
    enum class Song{
        BGM = 0,
        SOLID,
        BLEEPMP3,
        BLEEPWAV,
        POWERUP,
        IKUN,
        JI
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