#include "soundEngine.h"
#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif
SoundEngine::~SoundEngine()
{
    if (sound_engine)
        delete sound_engine;
}
void SoundEngine::play_music(Song song)
{
    switch (song)
    {
    case BGM:
        sound_engine->play2D(PROJECT_DIR "/assets/music/breakout.mp3", true);
        break;
    case SOLID:
        sound_engine->play2D(PROJECT_DIR "/assets/music/solid.wav", false);
        break;
    case BLEEPMP3:
        sound_engine->play2D(PROJECT_DIR "/assets/music/bleep.mp3", false);
        break;
    case BLEEPWAV:
        sound_engine->play2D(PROJECT_DIR "/assets/music/bleep.wav", false);
        break;
    case POWERUP:
        sound_engine->play2D(PROJECT_DIR "/assets/music/powerup.wav", false);
        break;
    default:
        __debugbreak();
        break;
    }
}
SoundEngine::SoundEngine()
{
    sound_engine = irrklang::createIrrKlangDevice();
}
