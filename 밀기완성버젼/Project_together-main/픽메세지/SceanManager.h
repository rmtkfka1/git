#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager)


public:
	void Init();
	void Update();
	void Render(HDC mdc);
	void Clear();
	void ChangeScene(SceneType sceneType);

private:
	Scene* _scene; //현재 실행하고있는 씬
	SceneType _sceneType = SceneType::NONE; //씬타입(STAGE1,STAGE2,STAGE3)
};

