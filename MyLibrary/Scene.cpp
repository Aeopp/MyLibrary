#include "Scene.h"
#include <algorithm>

Scene::~Scene() noexcept
{
	release();
}

void Scene::update(float dt)
{
	// TODO :: 오브젝트 사망처ㅣㄹ 
	std::erase_if(manage_objs,
		[](auto& Target) {if (!Target)return true; 
	
	
	return Target->bDie; });
}

void Scene::release()
{
	// TODO :: 오브젝트 사망처ㅣㄹ
	
	for (auto& obj : manage_objs)
	{
		if (!obj)continue;
		// 여기서 오브젝트 사망처리
		// 
		//obj->bDie = true;
	}
	manage_objs.clear();
}
