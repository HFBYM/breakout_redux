#include"brick.h"
#include"particle_generator.h"
#include"soundEngine.h"
#include"buffManager.h"

void Brick::log_all()
{
	log_renderer();
	log_collision();
}

void Brick::detach_all()
{
	detach_renderer();
	detach_collision();
}

void Brick::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
	if(!isSolid)
	{
		this->detach_all();
		ParticleGenerator::instance().log(this->id_name, this->id_num, std::make_unique<ParticleGenerator::Data>(pos, velocity, size, color, true));
		//TODO 更改声音命名
		SoundEngine::instance().play_music(SoundEngine::Song::SOLID);
		BuffManager::instance().createBuff(pos, glm::vec2(size.x, size.y/2.0f));
	}
	else
	{
		SoundEngine::instance().play_music(SoundEngine::Song::BLEEPMP3);
	}
}
