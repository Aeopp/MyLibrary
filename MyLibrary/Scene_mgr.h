#pragma once
#include <map>

#include "singleton_interface.h"
#include "ESceneID.h"
#include "Scene.h"
#include <functional>

class Scene_mgr : public  singleton_interface<Scene_mgr>
{
public:
	void Scene_Change(ESceneID _ESceneID);
	void render(HDC hdc, std::pair<float, float> size_factor);
	void update(float dt);
	void initialize();
	void release();

	template<ESceneID TargetID, typename TargetSceneType,
	typename...Params>
	void SceneRegist(Params&&... _Params);
private:
	std::shared_ptr<class Scene> sp_scene{};
	ESceneID _PreScene{ ESceneID::ENone };
	ESceneID _CurScene{ ESceneID::ENone };

	std::map<ESceneID, std::function<std::shared_ptr<Scene>()>> MakeSceneTypeMap;
};

template <ESceneID TargetID, typename TargetSceneType, typename...Params>
void Scene_mgr::SceneRegist(Params&&... _Params)
{
	static_assert(std::is_base_of_v<Scene, TargetSceneType>,L"Scene Type CompileError");
	
	MakeSceneTypeMap[TargetID] = [&](){

		return std::make_shared<TargetSceneType>(std::forward<Params>(_Params)...);};
}

