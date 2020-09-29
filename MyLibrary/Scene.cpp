#include "Scene.h"
#include <algorithm>

Scene::~Scene() noexcept
{
	release();
}

void Scene::update(float dt)
{
	// TODO :: ������Ʈ ���ó�Ӥ� 
	std::erase_if(manage_objs,
		[](auto& Target) {if (!Target)return true; 
	
	
	return Target->bDie; });
}

void Scene::release()
{
	// TODO :: ������Ʈ ���ó�Ӥ�
	
	for (auto& obj : manage_objs)
	{
		if (!obj)continue;
		// ���⼭ ������Ʈ ���ó��
		// 
		//obj->bDie = true;
	}
	manage_objs.clear();
}
