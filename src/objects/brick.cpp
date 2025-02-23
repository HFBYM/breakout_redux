/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 13:31:19
 * @FilePath: \breakout_redux\src\objects\brick.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "objects/brick.h"

#include <string>
#include <memory>

#include "engines/particle_generator.h"
#include "engines/soundEngine.h"
#include "engines/buffManager.h"
namespace brick
{
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

	void Brick::do_collision(const std::string &message,
							 const glm::vec2 &reflect, const glm::vec2 &offset)
	{
		using buff_manager::BuffManager;
		using particle_generator::ParticleGenerator;
		using sound_engine::SoundEngine;
		if (!isSolid)
		{
			this->detach_all();
			ParticleGenerator::instance().log(getIdName(), getIdNum(),
											  std::make_unique<particle_generator::ParticleData>(getPos(),
																								 getVelocity(), getSize(), getColor(), true));
			SoundEngine::instance().play_music("SOLID");
			BuffManager::instance().createBuff(getPos(), glm::vec2(getSize().x, getSize().y / 2.0f));
		}
		else
		{
			SoundEngine::instance().play_music("BLEEPMP3");
		}
	}
} // namespace brick
