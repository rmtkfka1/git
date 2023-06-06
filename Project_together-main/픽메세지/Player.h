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
	Pos	GetDiffP1() { return _DiffP1; }		// player1�� ���̰�
	Pos	GetDiffP2() { return _DiffP2; }		// player2�� ���̰�
	ObjectType& GetTurn() { return _turn; }
	void GapUpdate(KeyType);
	bool& GetDivide() { return _divide; }


	void jump1();
	void jump2();

	/// ī�޶� �̵� ��ȯ ó��
	void CameraGap();


public:
	Pos				_posP1{};			// player1�� ���� ��ġ
	Pos				_RenderPosP1{};		// player1�� ������ â ��ġ
	Pos				_CenterPosP1{};		// �߽���ġ
	Pos				_DiffP1{};			// ���� ��ġ�� ������ â ��ġ�� ���� ��
	int				_motion_cntP1{ };

	CImage			player1_img_left;
	CImage			player1_img_right;
	CImage          fire_img;

	BOOL			FIRE;
	int			fire_count = 0;

	Motion			_motionP1;

	HDC				mdcP1;
	HBITMAP			hBitmapP1;

	////////////////////////////////////////////////////////////////////

	Pos				_posP2{};			// player2�� ���� ��ġ
	Pos				_RenderPosP2{};		// player2�� ������ â ��ġ
	Pos				_CenterPosP2{};		// �߽���ġ
	Pos				_DiffP2{};			// ���� ��ġ�� ������ â ��ġ�� ���� ��
	int				_motion_cntP2{ };

	CImage			player2_img_left;
	CImage			player2_img_right;

	Motion			_motionP2;

	HDC				mdcP2;
	HBITMAP			hBitmapP2;

	bool			_divide{ false };
	ObjectType		_turn{ ObjectType::PLAYER1 };
	BackGround* _background{ nullptr };

	//////////////////////////////////////////////////////
	//����



	float   JumpTime1 = 0.f;
	float   JumpHeight1 = 0;
	float   jumpPower1 = 45.f;
	float temp1 = 0;
	BOOL   rand1;
	BOOL Gravity1;
	BOOL   g_bJumpkeyPressed1 = FALSE;	//	���� Ű Space bar�� ������ TRUE�� ����
	
	float   JumpTime2 = 0.f;
	float   JumpHeight2 = 0;
	float   jumpPower2 = 45.f;
	float temp2 = 0;
	BOOL   rand2;
	BOOL Gravity2;
	BOOL   g_bJumpkeyPressed2 = FALSE;	//	���� Ű Space bar�� ������ TRUE�� ����

	WCHAR test[100];



};



