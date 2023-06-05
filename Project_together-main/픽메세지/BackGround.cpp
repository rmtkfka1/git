#include "pch.h"
#include "BackGround.h"
#include "Stage1.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "Player.h"



BackGround::BackGround() :Object(ObjectType::PLAYER1)
{
}

BackGround::~BackGround()
{
	background_img.Destroy();
	
}

void BackGround::Init(){
	background_img.Load(L"리소스\\BackGround.png");


	_PosP1 = { 0, static_cast<float>(background_img.GetHeight() - WINDOW_HEIGHT)};
	_PosP2 = { 0, static_cast<float>(background_img.GetHeight() - WINDOW_HEIGHT) };
	_RenderposP1 = _PosP1;
	_RenderposP2 = _PosP2;


	// 테스트용도
	_tileTest = { 0, WINDOW_HEIGHT - 170, static_cast<long>(background_img.GetWidth() * 1.8), WINDOW_HEIGHT };

	CTest.Load(L"리소스\\타일셋.jpg");
	_CPos = {0, 439+32};
	_CRenderposP1 = _CPos;
}


void BackGround::Update()
{



}

void BackGround::Render(HDC mdc){}

void BackGround::Render(HDC& mdc, Pos diff1, Pos diff2, ObjectType Choose, bool _divide)
{

	hbit2 = CreateCompatibleBitmap(mdc, background_img.GetWidth(), background_img.GetHeight());
	mdc2 = CreateCompatibleDC(mdc);
	SelectObject(mdc2, (HBRUSH)hbit2);

	_RenderposP1 = _PosP1 + diff1 * 0.25f;
	_RenderposP2 = _PosP2 + diff2 * 0.25f;

	background_img.Draw(mdc2, 0, 0, background_img.GetWidth(), background_img.GetHeight()
		, 0, 0, background_img.GetWidth(), background_img.GetHeight());



	if (_RenderposP1.y < 0)
		_RenderposP1.y = 0;

	if (_RenderposP2.y < 0)
		_RenderposP2.y = 0;

	if (Choose == ObjectType::PLAYER1) {

		if (_RenderposP1.x > background_img.GetWidth() - WINDOW_WIDTH) {
			_RenderposP1.x = background_img.GetWidth() - WINDOW_WIDTH;
		}
		else
			renderTest = diff1 - _tileTest;
	}
	else {
		if (_RenderposP2.x > background_img.GetWidth() - WINDOW_WIDTH) {
			_RenderposP2.x = background_img.GetWidth() - WINDOW_WIDTH;
		}
		else
			renderTest = diff2 - _tileTest;
	}



	// 화면 분할 x
	if (_divide == false) {
		if (Choose == ObjectType::PLAYER1)
			TransparentBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
				mdc2, _RenderposP1.x, _RenderposP1.y, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0));
		else
			TransparentBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
				mdc2, _RenderposP2.x, _RenderposP2.y, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0));


		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
		oldBrush = (HBRUSH)SelectObject(mdc, hBrush);

		FrameRect(mdc, &renderTest, hBrush);
		SelectObject(mdc, oldBrush);
		DeleteObject(hBrush); // 만든 브러시 객체 삭제하기
	}

	// 화면 분할 o
	else if (_divide == true) {

		TransparentBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2,
			mdc2, _RenderposP1.x, _RenderposP1.y, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0));

		TransparentBlt(mdc, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2,
			mdc2, _RenderposP2.x, _RenderposP2.y, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0));

	}



	DeleteDC(mdc2);
	DeleteObject(hbit2);

	TileRender(mdc);
}

void BackGround::TileRender(HDC& mdc)
{
	

	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는것
	Player* p = player[0];
	
	Pos diff = p->GetDiffP1();
	Pos diff2 = p->GetDiffP2();
	
	if(p->_turn== ObjectType::PLAYER1)			// 초점이 1일 때
		_CRenderposP1 = _CPos - diff;			// << player1일 때
	else if(p->_turn == ObjectType::PLAYER2)	// 초점이 2
		_CRenderposP1 = _CPos - diff2;			// << player2일 때

	

	hbit2 = CreateCompatibleBitmap(mdc, CTest.GetWidth(), CTest.GetHeight());
	mdc2 = CreateCompatibleDC(mdc);
	SelectObject(mdc2, (HBRUSH)hbit2);

	CTest.Draw(mdc2, 0, 0, CTest.GetWidth(), CTest.GetHeight()
		, 0, 0, CTest.GetWidth(), CTest.GetHeight());

	TransparentBlt(mdc, _CRenderposP1.x, _CRenderposP1.y, static_cast<float>(background_img.GetWidth() * 5.0), 200,
		mdc2, 0, 0, CTest.GetWidth(), CTest.GetHeight(), RGB(0, 0, 0));

	DeleteDC(mdc2);
	DeleteObject(hbit2);
	


}

