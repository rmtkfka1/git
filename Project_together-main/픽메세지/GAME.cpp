#include "pch.h"
#include "GAME.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceanManager.h"


GAME::~GAME()
{

}

void GAME::Init(HWND _hwnd)
{
	hwnd =_hwnd;
	hdc = GetDC(_hwnd);
	//더블버퍼링
	mdc = CreateCompatibleDC(hdc);
	hbitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	HBITMAP prev = (HBITMAP)SelectObject(mdc, hbitmap);
	DeleteObject(prev);
	//더블버퍼링 처리

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(KeyManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::STAGE1);
	
}

void GAME::Update()
{

	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(KeyManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	//GET_SINGLE(CameraManager)->Update();
}

void GAME::Render()
{
	GET_SINGLE(SceneManager)->Render(mdc);


	{
		POINT MOUSEPOSE = GET_SINGLE(KeyManager)->GetMousePos();

		wstring str = std::format(L"Mouse({0},{1})", MOUSEPOSE.x, MOUSEPOSE.y);
		TextOut(mdc, 0, 0, str.c_str(), static_cast<int32>(str.size()));
	}

	BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, mdc, 0, 0, SRCCOPY);
	PatBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITENESS); // INVAILDRECT 대체 하는 함수
}

