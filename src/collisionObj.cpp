#include"collisionObj.h"
#include"collision.h"
#include"check.h"
CollisionObj::~CollisionObj()
{
    ASSERT_LOG(!is_log_collision, "ERROR::COLLISIONOBJ: " << id_name.getStr() << " "
    << id_num << "isn't detached in movement");
}

void CollisionObj::log_collision()
{
    if(!is_log_collision)
    {
      std::function<void(const mString &)> func = [this](const mString &message)
      { this->do_collision(message); };
      Collision::log(id_name, func, id_num, pos, size);
    }	
  is_log_collision = true;
}

void CollisionObj::detach_collision()
{
    if(is_log_collision)
		Collision::detach(id_name, id_num);
	is_log_collision = false;
}
