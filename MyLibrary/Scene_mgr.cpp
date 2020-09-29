#include "Scene_mgr.h"

void Scene_mgr::Scene_Change(ESceneID _ESceneID)
{
	_CurScene = _ESceneID;
	if (_PreScene != _CurScene)
	{
		if (sp_scene)
		{
			sp_scene.reset();
		}
		
		sp_scene = MakeSceneTypeMap[_ESceneID]();
		
		sp_scene->initialize();
		_PreScene = _CurScene;
	}
}

void Scene_mgr::render(HDC hdc, std::pair<float, float> size_factor)
{
	if (!sp_scene)return;
	sp_scene->render(hdc, size_factor);
}

void Scene_mgr::update(float dt)
{
	if (!sp_scene)return;
	sp_scene->update(dt);
}

void Scene_mgr::initialize()
{

	if (!sp_scene)return;
	sp_scene->initialize();
}

void Scene_mgr::release()
{
	if (!sp_scene)return;
	sp_scene->release();
}
