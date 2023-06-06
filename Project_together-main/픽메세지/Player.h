#pragma once
#include "Object.h"

class BackGround;

class Player :public Object
{

public:


	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;


	void Init(BackGround*);

	void CRender(HDC mdc);
	Pos	GetDiffP1() { return _DiffP1; }		// player1의 차이값
	Pos	GetDiffP2() { return _DiffP2; }		// player2의 차이값
	ObjectType& GetTurn() { return _turn; }
	void GapUpdate(KeyType);
	bool& GetDivide() { return _divide; }


	void jump1();
	void jump2();

	/// 카메라 이동 전환 처리
	void CameraGap();
	void CollisionGap();

	// 넉백 추가
	void KnocBackP1();
	void KnocBackP2();

	// player2의 밀기
	void Push();

public:

	// Player1
	////////////////////////////////////////////////////////////////////


	Pos				_posP1{};			// player1의 실제 위치
	Pos				_RenderPosP1{};		// player1의 윈도우 창 위치
	Pos				_CenterPosP1{};		// 중심위치
	Pos				_DiffP1{};			// 실제 위치와 윈도우 창 위치에 차이 값
	float			_motion_cntP1{ };

	CImage			player1_img_left;
	CImage			player1_img_right;

	CImage          fire_img;

	Motion			_motionP1;

	HDC				mdcP1;
	HBITMAP			hBitmapP1;

	// 점프
	CImage			player1_img_jump;
	Motion			JumpMotionP1;
	float			JumpTime1 = 0.f;
	float			JumpHeight1 = 0;
	float			jumpPower1 = 45.f;
	float			temp1 = 0;
	BOOL			rand1;
	BOOL			Gravity1;
	BOOL			g_bJumpkeyPressed1 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경

	// 넉백 부분 추가 부분
	CImage          player1_img_hurt_left;
	CImage          player1_img_hurt_right;
	BOOL			_KnocBackP1{ false };
	Pos				_KnockPosP1{};

	// 사다리 추가 부분
	CImage			player1_img_Climb;


	// Player2
	////////////////////////////////////////////////////////////////////

	Pos				_posP2{};			// player2의 실제 위치
	Pos				_RenderPosP2{};		// player2의 윈도우 창 위치
	Pos				_CenterPosP2{};		// 중심위치
	Pos				_DiffP2{};			// 실제 위치와 윈도우 창 위치에 차이 값
	float				_motion_cntP2{ };

	CImage			player2_img_left;
	CImage			player2_img_right;

	Motion			_motionP2;

	HDC				mdcP2;
	HBITMAP			hBitmapP2;

	// 넉백 부분 추가 부분
	CImage          player2_img_hurt_left;
	CImage          player2_img_hurt_right;
	BOOL			_KnocBackP2{ false };
	Pos				_KnockPosP2{};

	//점프
	CImage			player2_img_jump;
	Motion			JumpMotionP2;
	float			JumpTime2 = 0.f;
	float			JumpHeight2 = 0;
	float			jumpPower2 = 45.f;
	float			temp2 = 0;
	BOOL			rand2;
	BOOL			Gravity2;
	BOOL			g_bJumpkeyPressed2 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경

	// 사다리 추가 부분
	CImage			player2_img_Climb;

	// player2 밀기
	CImage			player2_img_push;

	// 공용
	////////////////////////////////////////////////////////////////////
	BOOL			FIRE;
	int				fire_count = 0;
	WCHAR			test[100];

	bool			_divide{ false };
	ObjectType		_turn{ ObjectType::PLAYER1 };
	BackGround* _background{ nullptr };


	// 카메라 추가 부분
	float			_collisionLeftP1{};
	float			_collisionLeftP2{};

};
