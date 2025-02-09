#include "soundEngine.h"
#include"debug.h"
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
    case Song::BGM:
        sound_engine->play2D(PROJECT_DIR "/assets/music/breakout.mp3", true);
        break;
    case Song::SOLID:
        sound_engine->play2D(PROJECT_DIR "/assets/music/solid.wav", false);
        break;
    case Song::BLEEPMP3:
        sound_engine->play2D(PROJECT_DIR "/assets/music/bleep.mp3", false);
        break;
    case Song::BLEEPWAV:
        sound_engine->play2D(PROJECT_DIR "/assets/music/bleep.wav", false);
        break;
    case Song::POWERUP:
        sound_engine->play2D(PROJECT_DIR "/assets/music/powerup.wav", false);
        break;
    case Song::IKUN:
        sound_engine->play2D(PROJECT_DIR "/assets/music/niganma.mp3", false);
        break;
    case Song::JI:
        sound_engine->play2D(PROJECT_DIR "/assets/music/zhiyin.mp3", false);
        break;
    default:
        MDEBUG();
        break;
    }
}
SoundEngine::SoundEngine()
{
    sound_engine = irrklang::createIrrKlangDevice();
}
