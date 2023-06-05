#pragma once


enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,
	SpaceBar = VK_SPACE,

	//플레이어1
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F',
	G = 'G',

	//플레이어2
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	J = 'J',
	K = 'K',
	Z = 'Z',
	X = 'X',
	I = '1',
	O='2',
	P='3',

};

enum class KeyState
{
	NONE,//아무것도 아닌상태
	PRESS, //누르고있는상태
	DOWN, //한번눌림
	UP, //키보드 자판땜
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::END)
};

enum class SceneType
{
	NONE,
	LOBBY,
	STAGE1,
	STAGE2,
	STAGE3,
	EDITSCENE,
	END,
};


enum class ObjectType
{
	NONE,
	PLAYER,
	PLAYER1,
	PLAYER2,
	PLAYERSUM,
	MONSTER,
	MISSILE,
	TILE,
	ENV,

};

enum class Motion
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

enum class Bullet_Dir
{
	LEFT,
	RIGHT,
	DOWN,
	UP,
};