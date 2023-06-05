#include "pch.h"
#include "Misile.h"
#include "pch.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Misile.h"
#include "Player.h"


Missile::Missile() :Object(ObjectType::MISSILE)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	size.x = 10;
	size.y = 10;
	_stat.hp = 1;
	_stat.maxhp = 1;
	_stat.speed = 1000;
}

void Missile::Update()
{

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_motion == Bullet_Dir::RIGHT)
	{
		_pos.x += _stat.speed * deltaTime;
	}
	if (_motion == Bullet_Dir::LEFT)
	{
		_pos.x -= _stat.speed * deltaTime;
	}


	//충돌처리구현//
	const vector<Missile*>& msilles = GET_SINGLE(ObjectManager)->GetMissile();   //벡터를 가져오는것
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는것
	Player* p = player[0];
	
	for (int i = 0; i < msilles.size(); ++i)
	{
		RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y +p->GetSize().y};
		RECT missile_rect = { msilles[i]->GetPos().x,msilles[i]->GetPos().y,msilles[i]->GetPos().x + msilles[i]->GetSize().x
			,msilles[i]->GetPos().y + msilles[i]->GetSize().y};
		RECT intersect_rect;

		if (IntersectRect(&intersect_rect, &missile_rect, &p2_rect))
		{
			
			Pos temp = p->_posP2;
			p->_posP2 = p->_posP1;
			p->_posP1 = temp;
			
			GET_SINGLE(ObjectManager)->Remove(msilles[i]);   //벡터를 가져오는것
			return;
		}
	}

	//객체삭제구현//
	if (_pos.x > 4000)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return; //삭제하면 무조건 리턴을 떄려야한다.
	}

	if (_pos.x < -4000)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return; //삭제하면 무조건 리턴을 떄려야한다.
	}
};



void Missile::Render(HDC hdc)
{
	size_t size = 15;
	
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는것
	Player* p = player[0]; 
	
	ObjectType turn = p->GetTurn();

	Pos RenderPos;
	if(turn == ObjectType::PLAYER1)
		RenderPos = _pos - p->GetDiffP1();
	else if(turn == ObjectType::PLAYER2)
		RenderPos = _pos - p->GetDiffP2();


	Ellipse(hdc, RenderPos.x, RenderPos.y, RenderPos.x + size, RenderPos.y + size);
	// 화면 분할 총알 부분 해결 못함

}

