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

	// Player1
	//==============================================================================//

	player1_img_left.Load(L"리소스\\ch1\\LEFT.png");
	player1_img_right.Load(L"리소스\\ch1\\RIGHT.png");

	// 넉백
	player1_img_hurt_left.Load(L"리소스\\ch1\\Pink_Monster_Hurt_4_LEFT.png");
	player1_img_hurt_right.Load(L"리소스\\ch1\\Pink_Monster_Hurt_4_RIGHT.png");

	_posP1 = { WINDOW_WIDTH / 2 ,  WINDOW_HEIGHT - 200 };
	_RenderPosP1 = _posP1;
	_CenterPosP1 = _posP1;

	// 사다리
	player1_img_Climb.Load(L"리소스\\ch1\\Pink_Monster_Climb_4.png");

	// 점프
	player1_img_jump.Load(L"리소스\\ch1\\PINKJUMP.png");

	JumpTime1 = 0.f;
	JumpHeight1 = 0;
	jumpPower1 = 45.0f;
	temp1 = 0.0f;
	g_bJumpkeyPressed1 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경
	Gravity1 = true;

	_motionP1 = Motion::RIGHT;
	//==============================================================================//
	player2_img_left.Load(L"리소스\\ch2\\LEFT.png");
	player2_img_right.Load(L"리소스\\ch2\\RIGHT.png");

	// 넉백
	player2_img_hurt_left.Load(L"리소스\\ch2\\Dude_Monster_Hurt_4_LEFT.png");
	player2_img_hurt_right.Load(L"리소스\\ch2\\Dude_Monster_Hurt_4_RIGHT.png");

	// 사다리
	player2_img_Climb.Load(L"리소스\\ch2\\Dude_Monster_Climb_4.png");

	_posP2 = { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200 };
	_RenderPosP2 = _posP2;
	_CenterPosP2 = _posP2;

	_motionP2 = Motion::RIGHT;

	// 점프
	player2_img_jump.Load(L"리소스\\ch2\\Dude_JUMP.png");

	JumpTime2 = 0.f;
	JumpHeight2 = 0;
	jumpPower2 = 45.0f;
	temp2 = 0.0f;
	Gravity2 = true;
	g_bJumpkeyPressed2 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경


	// 밀기
	//player2_img_push.Load()

	//=================================================================================//

	//공용
	_background = background;

	size.x = 32;
	size.y = 32;

	_stat.speed = 300;
	FIRE = FALSE;
	fire_img.Load(L"리소스\\fire.png");

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

	if ((!FIRE) && (!_KnocBackP1))
	{

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::A))
		{

			_motionP1 = Motion::LEFT;
			_posP1.x -= _stat.speed * deletaTime;
			_motion_cntP1 += deletaTime * 10;
			if (_motion_cntP1 > 5.f)
				_motion_cntP1 = 0.f;
			//_motion_cntP1 = (_motion_cntP1 + 1) % 6;

			if (_posP1.x < WINDOW_WIDTH / 2)
				_RenderPosP1.x -= _stat.speed * deletaTime;
			else if (_posP1.x > background->background_img.GetWidth() * 1.8)
				_RenderPosP1.x -= _stat.speed * deletaTime;

		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::D))
		{
			_motionP1 = Motion::RIGHT;
			_posP1.x += _stat.speed * deletaTime;
			_motion_cntP1 += deletaTime * 10;
			if (_motion_cntP1 > 5.f)
				_motion_cntP1 = 0.f;
			//_motion_cntP1 = (_motion_cntP1 + 1) % 6;


			if (_posP1.x < WINDOW_WIDTH / 2)
				_RenderPosP1.x += _stat.speed * deletaTime;
			else if (_posP1.x > background->background_img.GetWidth() * 1.8)
				_RenderPosP1.x += _stat.speed * deletaTime;
		}


		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::F))
		{
			g_bJumpkeyPressed1 = TRUE;
			JumpMotionP1 = Motion::UP;
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
			_motion_cntP2 += deletaTime * 10;
			if (_motion_cntP2 > 5.f)
				_motion_cntP2 = 0.f;

			if (_posP2.x < WINDOW_WIDTH / 2)
				_RenderPosP2.x -= _stat.speed * deletaTime;

		}

		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::Right))
		{
			_motionP2 = Motion::RIGHT;
			_posP2.x += _stat.speed * deletaTime;
			_motion_cntP2 += deletaTime * 10;
			if (_motion_cntP2 > 5.f)
				_motion_cntP2 = 0.f;


			if (_posP2.x < WINDOW_WIDTH / 2)
				_RenderPosP2.x += _stat.speed * deletaTime;
		}


		if (GET_SINGLE(KeyManager)->Getbutton(KeyType::J))
		{
			g_bJumpkeyPressed2 = TRUE;
			JumpMotionP2 = Motion::UP;

		}

	}

	CameraGap();


	jump1();
	jump2();

	KnocBackP1();
	KnocBackP2();

	if (Gravity1)
	{
		_posP1.y += 10;
	}
	if (Gravity2)
	{
		_posP2.y += 10;
	}
	//_posP1.y += 3;
	//_posP2.y += 3;

	//임시로 막아둔것



}

void Player::CRender(HDC mdc) {

	// player1
	// ====================================

	hBitmapP1 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	mdcP1 = CreateCompatibleDC(mdc);
	SelectObject(mdcP1, (HBITMAP)hBitmapP1);

	if (FIRE)
	{
		fire_img.Draw(mdcP1, 0, 0, size.x, size.y, fire_count * 48, 0, 48, 48);
	}
	else if (_KnocBackP1)
	{
		if (_motionP1 == Motion::LEFT)
		{
			player1_img_hurt_left.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);
		}

		if (_motionP1 == Motion::RIGHT)
		{
			player1_img_hurt_right.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);

		}
	}
	else if (g_bJumpkeyPressed1)
	{
		if (JumpMotionP1 == Motion::UP)
		{
			player1_img_jump.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);
		}

		if (JumpMotionP1 == Motion::DOWN)
		{
			player1_img_jump.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);

		}
	}

	else {
		int moveCnt = static_cast<int>(_motion_cntP1);
		if (_motionP1 == Motion::LEFT)
		{
			player1_img_left.Draw(mdcP1, 0, 0, size.x, size.y, moveCnt * 32, 0, 32, 32);
		}

		if (_motionP1 == Motion::RIGHT)
		{

			player1_img_right.Draw(mdcP1, 0, 0, size.x, size.y, moveCnt * 32, 0, 32, 32);

		}
		if (_motionP1 == Motion::UP || _motionP1 == Motion::DOWN) {
			player1_img_Climb.Draw(mdcP1, 0, 0, size.x, size.y, moveCnt * 32, 0, 32, 32);
		}
	}

	// player2
	// ====================================


	hBitmapP2 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	mdcP2 = CreateCompatibleDC(mdc);
	SelectObject(mdcP2, (HBITMAP)hBitmapP2);

	if (FIRE) {
		fire_img.Draw(mdcP2, 0, 0, size.x, size.y, fire_count * 48, 0, 48, 48);
	}

	else if (_KnocBackP2)
	{
		if (_motionP2 == Motion::LEFT)
		{
			player2_img_hurt_left.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);
		}

		if (_motionP2 == Motion::RIGHT)
		{
			player2_img_hurt_right.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);

		}
	}
	else if (g_bJumpkeyPressed2)
	{
		if (JumpMotionP2 == Motion::UP)
		{
			player2_img_jump.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);
		}

		if (JumpMotionP2 == Motion::DOWN)
		{
			player2_img_jump.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);

		}
	}
	else
	{
		int moveCnt = static_cast<int>(_motion_cntP2);
		if (_motionP2 == Motion::LEFT)
		{
			player2_img_left.Draw(mdcP2, 0, 0, size.x, size.y, moveCnt * 32, 0, 32, 32);
		}

		if (_motionP2 == Motion::RIGHT)
		{
			player2_img_right.Draw(mdcP2, 0, 0, size.x, size.y, moveCnt * 32, 0, 32, 32);

		}
		if (_motionP2 == Motion::UP || _motionP2 == Motion::DOWN) {
			player2_img_Climb.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);
		}
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


	swprintf_s(test, L"p1->y :%.1f", _posP1.y);
	TextOut(mdc, 0, 0, test, lstrlen(test));

	swprintf_s(test, L"p2->y :%.1f", _posP2.y);
	TextOut(mdc, 0, 20, test, lstrlen(test));

	swprintf_s(test, L"renderp1->x :%.1f", _RenderPosP1.x);
	TextOut(mdc, 0, 35, test, lstrlen(test));

	swprintf_s(test, L"renderp2->y :%.1f", _RenderPosP2.x);
	TextOut(mdc, 0, 50, test, lstrlen(test));

	swprintf_s(test, L"_motion_cntP1 :%.1f", _motion_cntP1);
	TextOut(mdc, 0, 70, test, lstrlen(test));



	DeleteObject(hBitmapP1);
	DeleteDC(mdcP1);
	DeleteObject(hBitmapP2);
	DeleteDC(mdcP2);
}




// 애니메이션 처리 함수
void Player::jump1()
{

	if (!g_bJumpkeyPressed1) return;
	Gravity1 = false;
	JumpHeight1 = (JumpTime1 * JumpTime1 - jumpPower1 * JumpTime1) / 4.0f;
	_posP1.y += JumpHeight1 - temp1;
	temp1 = JumpHeight1;

	JumpTime1 += 1.1f;		//값을 올리면 점프속도가 빨라짐

	if (JumpHeight1 < -126.5f) {
		JumpMotionP1 = Motion::DOWN;
	}

	if (JumpMotionP1 == Motion::UP) {
		if (_motionP1 == Motion::RIGHT)
			_motion_cntP1 = 0;
		else if (_motionP1 == Motion::LEFT)
			_motion_cntP1 = 2;
	}
	else if (JumpMotionP1 == Motion::DOWN) {
		if (_motionP1 == Motion::RIGHT)
			_motion_cntP1 = 1;
		else if (_motionP1 == Motion::LEFT)
			_motion_cntP1 = 3;
	}



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
		Gravity1 = true;
		g_bJumpkeyPressed1 = FALSE;


	}

}


void Player::jump2()
{
	if (!g_bJumpkeyPressed2) return;
	Gravity2 = false;
	JumpHeight2 = (JumpTime2 * JumpTime2 - jumpPower2 * JumpTime2) / 4.f;
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

	if (JumpHeight2 < -126.5f) {
		JumpMotionP2 = Motion::DOWN;
	}

	if (JumpMotionP2 == Motion::UP) {
		if (_motionP2 == Motion::RIGHT)
			_motion_cntP2 = 0;
		else if (_motionP2 == Motion::LEFT)
			_motion_cntP2 = 2;
	}
	else if (JumpMotionP2 == Motion::DOWN) {
		if (_motionP2 == Motion::RIGHT)
			_motion_cntP2 = 1;
		else if (_motionP2 == Motion::LEFT)
			_motion_cntP2 = 3;
	}

	if (JumpTime2 > jumpPower2)
	{

		temp2 = 0;
		JumpTime2 = 0;
		JumpHeight2 = 0;
		g_bJumpkeyPressed2 = FALSE;
		Gravity2 = true;
	}

}

// 넉백 처리 함수
void Player::KnocBackP1()
{
	if (!_KnocBackP1) return;


	if (_motionP1 == Motion::RIGHT) {

		_motion_cntP1 = 1.f;
		_posP1.x -= 5.f;
		if (_posP1.x < _KnockPosP1.x)
			_KnocBackP1 = false;
	}
	else if (_motionP1 == Motion::LEFT) {
		_motion_cntP1 = 2.f;
		_posP1.x += 5.f;
		if (_posP1.x > _KnockPosP1.x)
			_KnocBackP1 = false;
	}


}

void Player::KnocBackP2()
{
	if (!_KnocBackP2) return;

	if (_motionP2 == Motion::RIGHT) {
		_motion_cntP2 = 1.f;
		_posP2.x -= 5.f;
		if (_posP2.x < _KnockPosP2.x)
			_KnocBackP2 = false;
	}
	else if (_motionP2 == Motion::LEFT) {
		_motion_cntP2 = 2.f;
		_posP2.x += 5.f;
		if (_posP2.x > _KnockPosP2.x)
			_KnocBackP2 = false;
	}
}

// player2 밀기
void Player::Push()
{


}


// 카메라 처리 함수

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