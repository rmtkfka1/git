#pragma once
#include "Object.h"


class BackGround :public Object
{
public:


	BackGround();
	virtual ~BackGround() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	


	void Render(HDC& mdc, Pos diff1, Pos diff2, ObjectType Choose, bool);

	void TileRender(HDC& mdc);

public:

	Pos			_PosP1{};			// player1에 초점
	Pos			_PosP2{};			// player2에 초점
	Pos			_RenderposP1{};		// player1에 초점시 윈도우 출력
	Pos			_RenderposP2{};		// player2에 초점시 윈도우 출력

	HDC			 mdc2;
	HBITMAP		hbit2;
	CImage		background_img;


	//타일 테스트용
	RECT		_tileTest{};
	RECT		renderTest{};
	Pos			_CPos{};				// 실제 좌표
	Pos			_CRenderposP1{};		// 렌더링 좌표
	CImage		CTest;

};

