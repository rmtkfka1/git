#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "Stage1.h"
#include "GAME.h"
#include "Object.h"
#include "BackGround.h"
#include "Misile.h"
#include "ObjectManager.h"
#include "Tile_P2.h"
#include "Tile_P1.h"
void Player::Render(HDC mdc) {}
void Player::Init() {}

Player::Player() :Object(ObjectType::PLAYER)
{
	

}

Player::~Player()
{

	player1_img_left.Destroy();
	player1_img_right.Destroy();
	

	player2_img_left.Destroy();
	player2_img_right.Destroy();
	fire_img.Destroy();
}


void Player::Init(BackGround* background) {

	_background = background;
	player1_img_left.Load(L"리소스\\ch1\\LEFT.png");
	player1_img_right.Load(L"리소스\\ch1\\RIGHT.png");


	_posP1 = { WINDOW_WIDTH / 2 ,  WINDOW_HEIGHT - 200 };
	_RenderPosP1 = _posP1;
	_CenterPosP1 = _posP1;

	player2_img_left.Load(L"리소스\\ch2\\LEFT.png");
	player2_img_right.Load(L"리소스\\ch2\\RIGHT.png");
	fire_img.Load(L"리소스\\fire.png");

	JumpTime1 = 0.f;
	JumpHeight1 = 0;
	jumpPower1 = 45.0f;
	temp1 = 0.0f;
	g_bJumpkeyPressed1 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경
	Gravity1 = true;
	Rand1 = false;

	_motionP1 = Motion::RIGHT;

//==============================================================================//

	_posP2 = { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200 };
	_RenderPosP2 = _posP2;
	_CenterPosP2 = _posP2;

	_motionP2 = Motion::RIGHT;


	JumpTime2 = 0.f;
	JumpHeight2 = 0;
	jumpPower2 = 45.0f;
	temp2 = 0.0f;
	Gravity2 = true;
	g_bJumpkeyPressed2 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경
	Rand2 = false;

	
//=================================================================================//

//공용
	size.x = 32;
	size.y = 32;

	_stat.speed = 300;
	FIRE = FALSE;
}


void Player::Update() {
	
	
	float deletaTime = GET_SINGLE(TimeManager)->GetDeltaTime(); //프레임동기화 (컴퓨터마다 속도를 똑같이맞춰줌)

	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::I))
		GapUpdate(KeyType::I);
	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::O))
		GapUpdate(KeyType::O);
	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::P))
		GapUpdate(KeyType::P);

	const vector<BackGround*>& bk = GET_SINGLE(ObjectManager)->GetBackGround();   //벡터를 가져오는것
	BackGround* background = bk[0];
	
	fire_count += 1;
	fire_count %= 12;

	// player1
	// =========================================================================================

	if (!FIRE)
	{
		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::A))
		{

			_motionP1 = Motion::LEFT;
			_posP1.x -= _stat.speed * deletaTime;
			_motion_cntP1 = (_motion_cntP1 + 1) % 6;

			if (_posP1.x < WINDOW_WIDTH / 2)
				_RenderPosP1.x -= _stat.speed * deletaTime;
			else if (_posP1.x > background->background_img.GetWidth() * 1.8)
				_RenderPosP1.x -= _stat.speed * deletaTime ;

		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::D))
		{

			_motionP1 = Motion::RIGHT;
			_posP1.x += _stat.speed * deletaTime;
			_motion_cntP1 = (_motion_cntP1 + 1) % 6;


			if (_posP1.x < WINDOW_WIDTH / 2)
				_RenderPosP1.x += _stat.speed * deletaTime ;
			else if (_posP1.x > background->background_img.GetWidth() * 1.8)
				_RenderPosP1.x += _stat.speed * deletaTime ;
		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::W))
		{
			_motionP1 = Motion::RIGHT;
			_posP1.y -= _stat.speed*10 * deletaTime;
			_motion_cntP1 = (_motion_cntP1 + 1) % 6;

		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::S))
		{
			_motionP1 = Motion::RIGHT;
			_posP1.y += _stat.speed * deletaTime;
			_motion_cntP1 = (_motion_cntP1 + 1) % 6;

		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::F))
		{
			g_bJumpkeyPressed1 = TRUE;
		}

		if (GET_SINGLE(KeyManager)->GetbuttonDown(KeyType::G))
		{
			Missile* missle = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
			missle->Init();

			missle->SetPos(Pos(_posP1.x, _posP1.y)); //주인공 객체에서 생성


			if (_motionP1 == Motion::RIGHT)
			{
				missle->SetMotion(Bullet_Dir::RIGHT);
			}

			else if (_motionP1 == Motion::LEFT)
			{
				missle->SetMotion(Bullet_Dir::LEFT);
			}

			GET_SINGLE(ObjectManager)->Add(missle);
		}

		// player2
		// ==============================================================================
		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::Left))
		{
			_motionP2 = Motion::LEFT;
			_posP2.x -= _stat.speed * deletaTime;
			_motion_cntP2 = (_motion_cntP2 + 1) % 6;

			if (_posP2.x < WINDOW_WIDTH / 2)
				_RenderPosP2.x -= _stat.speed * deletaTime;

		}


		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::Up))
		{
			_motionP2 = Motion::RIGHT;
			_posP2.y -= _stat.speed * deletaTime *10;
			_motion_cntP2 = (_motion_cntP2 + 1) % 6;


			//if (_posP2.x < WINDOW_WIDTH / 2)
			//	_RenderPosP2.x += _stat.speed * deletaTime;

		}


		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::Right))
		{
			_motionP2 = Motion::RIGHT;
			_posP2.x += _stat.speed * deletaTime;
			_motion_cntP2 = (_motion_cntP2 + 1) % 6;


			if (_posP2.x < WINDOW_WIDTH / 2)
				_RenderPosP2.x += _stat.speed * deletaTime;

		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::J))
		{
			g_bJumpkeyPressed2 = TRUE;
		}

	}

	CameraGap();


	jump1();
	jump2();

	if (Gravity1)
	{
	_posP1.y += 10;
	}
	if (Gravity2)
	{
	_posP2.y += 10;
	}


	rand1 = false;
	rand2 = false;

}

void Player::CRender(HDC mdc) {

	// player1
	// ====================================

	hBitmapP1 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	mdcP1 = CreateCompatibleDC(mdc);
	SelectObject(mdcP1, (HBITMAP)hBitmapP1);

	if (!FIRE)
	{
		if (_motionP1 == Motion::LEFT)
		{
			player1_img_left.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);
		}

		if (_motionP1 == Motion::RIGHT)
		{
			player1_img_right.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);
		}

	}
	else
	{
		fire_img.Draw(mdcP1, 0, 0, size.x, size.y, fire_count * 48, 0, 48, 48);
	}
	// player2
	// ====================================

	
	hBitmapP2 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	mdcP2 = CreateCompatibleDC(mdc);
	SelectObject(mdcP2, (HBITMAP)hBitmapP2);

	if (!FIRE) {
		if (_motionP2 == Motion::LEFT)
		{
			player2_img_left.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);
		}

		if (_motionP2 == Motion::RIGHT)
		{
			player2_img_right.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);

		}
	}

	else
	{
		fire_img.Draw(mdcP2, 0, 0, size.x, size.y, fire_count*48, 0, 48, 48);
	}


	if (_divide == false) {
		if (_turn == ObjectType::PLAYER1)
			_RenderPosP2 = _posP2 - _DiffP1;
		else if (_turn == ObjectType::PLAYER2)
			_RenderPosP1 = _posP1 - _DiffP2;


		TransparentBlt(mdc, _RenderPosP1.x, _RenderPosP1.y, size.x, size.y,
			mdcP1, 0, 0, size.x, size.y, RGB(0, 0, 0));

		TransparentBlt(mdc, _RenderPosP2.x, _RenderPosP2.y, size.x, size.y,
			mdcP2, 0, 0, size.x, size.y, RGB(0, 0, 0));
	}

	else if (_divide = true) {

		{
			HDC				P1;
			HBITMAP			mapP1;

			mapP1 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
			P1 = CreateCompatibleDC(mdc);
			SelectObject(P1, (HBITMAP)mapP1);

			Pos RenderPosP2 = _posP2 - _DiffP1;


			TransparentBlt(P1, _RenderPosP1.x, _RenderPosP1.y, size.x, size.y * 2,
				mdcP1, 0, 0, size.x, size.y, RGB(0, 0, 0));

			TransparentBlt(P1, RenderPosP2.x, RenderPosP2.y, size.x, size.y * 2,
				mdcP2, 0, 0, size.x, size.y, RGB(0, 0, 0));

			TransparentBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2,
				P1, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0));

			DeleteObject(mapP1);
			DeleteDC(P1);

		}

		{
			HDC				P1;
			HBITMAP			mapP1;

			mapP1 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
			P1 = CreateCompatibleDC(mdc);
			SelectObject(P1, (HBITMAP)mapP1);

			Pos RenderPosP1 = _posP1 - _DiffP2;

			TransparentBlt(P1, RenderPosP1.x, RenderPosP1.y, size.x, size.y * 2,
				mdcP1, 0, 0, size.x, size.y, RGB(0, 0, 0));

			TransparentBlt(P1, _RenderPosP2.x, _RenderPosP2.y, size.x, size.y * 2,
				mdcP2, 0, 0, size.x, size.y, RGB(0, 0, 0));

			TransparentBlt(mdc, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2,
				P1, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(0, 0, 0));


			DeleteObject(mapP1);
			DeleteDC(P1);
		}

	}


	/*swprintf_s(test, L"p1->x :%.1f", _posP1.x);
	TextOut(mdc, 0, 0, test, lstrlen(test)); 

	swprintf_s(test, L"p1->y :%.1f", _posP2.x);
	TextOut(mdc, 0, 20, test, lstrlen(test));

	swprintf_s(test, L"renderp1->x :%.1f", _RenderPosP1.x);
	TextOut(mdc, 0, 35, test, lstrlen(test));

	swprintf_s(test, L"renderp2->y :%.1f", _RenderPosP2.x);
	TextOut(mdc, 0, 50, test, lstrlen(test));*/
	
	DeleteObject(hBitmapP1);
	DeleteDC(mdcP1);
	DeleteObject(hBitmapP2);
	DeleteDC(mdcP2);
}

void Player::GapUpdate(KeyType key)
{
	const vector<BackGround*>& bk = GET_SINGLE(ObjectManager)->GetBackGround();   //벡터를 가져오는것
	BackGround* background = bk[0];

	if (key == KeyType::I) {
		_divide = false;
		_turn = ObjectType::PLAYER1;


		if (_RenderPosP1 != _CenterPosP1) {
			_RenderPosP1 = _CenterPosP1;
			if (_posP1.x < WINDOW_WIDTH / 2) {
				_RenderPosP1.x = _posP1.x;
			}
			else if (_posP1.x > background->background_img.GetWidth() - WINDOW_WIDTH / 2)
				_RenderPosP1 = _posP1 - _DiffP1;

		}
	}
	else if (key == KeyType::O) {
		_divide = false;
		_turn = ObjectType::PLAYER2;

		if (_RenderPosP2 != _CenterPosP2) {
			_RenderPosP2 = _CenterPosP2;
			if (_posP2.x < WINDOW_WIDTH / 2) {
				_RenderPosP2.x = _posP2.x;
			}
			else if (_posP2.x > background->background_img.GetWidth() - WINDOW_WIDTH / 2)
				_RenderPosP2 = _posP2 - _DiffP2;
		}
	}


	// 화면 분할

	else if (key == KeyType::P) {
		_divide = true;
		_turn = ObjectType::PLAYERSUM;

		if (_RenderPosP1 != _CenterPosP1) {
			_RenderPosP1 = _CenterPosP1;
			if (_posP1.x < WINDOW_WIDTH / 2) {
				_RenderPosP1.x = _posP1.x;
			}
		}

		if (_RenderPosP2 != _CenterPosP2) {
			_RenderPosP2 = _CenterPosP2;
			if (_posP2.x < WINDOW_WIDTH / 2) {
				_RenderPosP2.x = _posP2.x;
			}
		}
	}



}


void Player::jump1()
{
	
	if (!g_bJumpkeyPressed1) return;
	Gravity1 = false;
	JumpHeight1 = (JumpTime1 * JumpTime1 - jumpPower1 * JumpTime1) / 4.0f ;
	_posP1.y += JumpHeight1 - temp1;
	temp1 = JumpHeight1;

	JumpTime1 += 1.1f;		//값을 올리면 점프속도가 빨라짐

	//if (rand1)
	//{
	//	JumpTime1 = 0.f;
	//	JumpHeight1 = 0;
	//	jumpPower1 = 60.f;
	//	temp1 = 0.0f;
	//	g_bJumpkeyPressed1 = FALSE;
	//	return;
	//}
	

	if (JumpTime1 > jumpPower1)
	{
		temp1 = 0;
		JumpTime1 = 0;
		JumpHeight1 = 0;
		g_bJumpkeyPressed1 = FALSE;
		Gravity1 = true;
	}
}


void Player::jump2()
{
	//if (!rand2) return;
	if (!g_bJumpkeyPressed2) return;
	Gravity2 = false;
	JumpHeight2 = (JumpTime2 * JumpTime2 - jumpPower2 * JumpTime2) / 4.f ;
	_posP2.y += JumpHeight2 - temp2;
	temp2 = JumpHeight2;

	JumpTime2 += 1.1f;		//값을 올리면 점프속도가 빨라짐

	//if (rand2)
	//{
	//	JumpTime2 = 0.f;
	//	JumpHeight2 = 0;
	//	jumpPower2 = 60.f;
	//	temp2 = 0.0f;
	//	g_bJumpkeyPressed2 = FALSE;
	//	return;
	//}

	if (JumpTime2 > jumpPower2)
	{

		temp2 = 0;
		JumpTime2 = 0;
		JumpHeight2 = 0;
		g_bJumpkeyPressed2 = FALSE;
		Gravity2 = true;
	}

}


void Player::CameraGap()
{
	const vector<BackGround*>& bk = GET_SINGLE(ObjectManager)->GetBackGround();   //벡터를 가져오는것
	BackGround* background = bk[0];

	_DiffP1 = _posP1 - _CenterPosP1;
	_DiffP2 = _posP2 - _CenterPosP2;


	if (_DiffP1.x < 0.f)
		_DiffP1.x = 0.f;

	if (_DiffP2.x < 0.f)
		_DiffP2.x = 0.f;


}

void Player::CollisionGap()
{
	if (_turn == ObjectType::PLAYER1) {
		if (_posP1.x < _CenterPosP1.x && _posP2.x < _CenterPosP2.x) {
			swap(_RenderPosP1.x, _RenderPosP2.x);
			swap(_collisionLeftP1, _collisionLeftP2);
		}
		else if (_posP2.x < _CenterPosP2.x) {
			_RenderPosP1.x += _collisionLeftP2;
			swap(_collisionLeftP1, _collisionLeftP2);

		}
		else if (_posP1.x < _CenterPosP1.x) {
			_RenderPosP1 = _CenterPosP1;
			swap(_collisionLeftP1, _collisionLeftP2);
		}

	}

	else if (_turn == ObjectType::PLAYER2) {
		if (_posP1.x < _CenterPosP1.x && _posP2.x < _CenterPosP2.x) {
			swap(_RenderPosP1.x, _RenderPosP2.x);
			swap(_collisionLeftP1, _collisionLeftP2);
		}
		else if (_posP2.x < _CenterPosP2.x) {
			_RenderPosP2 = _CenterPosP2;
			swap(_collisionLeftP1, _collisionLeftP2);

		}
		else if (_posP1.x < _CenterPosP1.x) {
			_RenderPosP2.x += _collisionLeftP1;
			swap(_collisionLeftP1, _collisionLeftP2);
		}
	}
}