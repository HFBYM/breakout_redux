#include "soundEngine.h"
#include "debug.h"
#include "resource_manager.h"
#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif
SoundEngine::~SoundEngine()
{
    if (sound_engine)
        delete sound_engine;
}
void SoundEngine::play_music(std::string song)
{
    const ResourceManager::json &data = ResourceManager::instance().getJsonData();
    std::string project_dir(PROJECT_DIR "/");
    for (const auto &[name, i] : data["resources"]["music"].get<std::map<std::string, ResourceManager::json>>())
        if (name == song)
        {
            auto path = project_dir + i["path"].get<std::string>();
            sound_engine->play2D(path.c_str(), i["isRepeated"].get<bool>());
            return;
        }
    MDEBUG();
}
SoundEngine::SoundEngine()
{
    sound_engine = irrklang::createIrrKlangDevice();
}
