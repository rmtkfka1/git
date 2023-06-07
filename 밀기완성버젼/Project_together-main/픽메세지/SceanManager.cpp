#include "pch.h"
#include "SceanManager.h"
#include "Stage1.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_scene)
	{
		_scene->Update();
	}

}

void SceneManager::Render(HDC mdc)
{
	if (_scene)
	{
		_scene->Render(mdc);
	}
}

void SceneManager::Clear()
{
	if (_scene)
	{
		delete _scene;
		_scene = nullptr;
	}
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::NONE:
		break;
	case SceneType::LOBBY:
		//newScene = new Lobby();
		break;
	case SceneType::STAGE1:
		newScene = new Stage1();
		break;
	case SceneType::STAGE2:
		/*newScene = new Stage2();*/
		break;
	case SceneType::STAGE3:
		/*newScene = new Stage3();*/
		break;
	case SceneType::END:

		break;
	default:
		break;
	}

	//이미씬이 존재하는 경우 씬삭제
	if (_scene)
	{
		delete _scene;
		_scene = nullptr;
	}

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
