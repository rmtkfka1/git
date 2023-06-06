#include "pch.h"
#include "Stage1.h"
#include "TimeManager.h"
#include "BackGround.h"
#include "KeyManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Misile.h"
#include "Tile_P1.h"
#include "Tile_P2.h"
#include "Tile.h"

Stage1::~Stage1()
{

}

void Stage1::Init()
{

	BackGround* bg = GET_SINGLE(ObjectManager)->CreateObject<BackGround>();
	bg->Init();
	GET_SINGLE(ObjectManager)->Add(bg); 

	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	GET_SINGLE(ObjectManager)->Add(player);
	player->Init(bg);

	//============================ Tile  만들기 ==============================//
	
	//사이즈세팅을 위해 매크로안썼음
	Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
	tile->SetPos(Pos(0, 439 + 32));
	tile->Init();
	tile->SetSize(Pos(4000, 200));
	GET_SINGLE(ObjectManager)->Add(tile);

	//벽쪽 추가
	Tile* tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
	tile2->SetPos(Pos(3400, -1000));
	tile2->Init();
	tile2->SetSize(Pos(700, 3000));
	GET_SINGLE(ObjectManager)->Add(tile2);



	//============================ Tile_P1 만들기 ==============================//
	{

		MakeTile_P1(1000, 400);

	}
	//============================ Tile_P2 만들기 ==============================//
	{

		MakeTile_P2(800, 400);
		MakeTile_P2(900, 300);
		MakeTile_P2(1100, 200);

	}

}

void Stage1::Update()
{


	const vector<BackGround*>& bg = GET_SINGLE(ObjectManager)->GetBackGround();
	bg[0]->Update();

	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();
	player[0]->Update();


	const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();
	for (int i = 0; i < missiles.size(); ++i)
	{
		missiles[i]->Update();
	}


	const vector<Tile*> tiles = GET_SINGLE(ObjectManager)->GetTile();
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Update();
	}



	const vector<Tile_P1*> tiles_p1 = GET_SINGLE(ObjectManager)->GetTile_P1();
	for (int i = 0; i < tiles_p1.size(); ++i)
	{
		tiles_p1[i]->Update();
	}



	const vector<Tile_P2*> tiles_p2 = GET_SINGLE(ObjectManager)->GetTile_P2();
	for (int i = 0; i < tiles_p2.size(); ++i)
	{
		tiles_p2[i]->Update();
	}


};


void Stage1::Render(HDC mdc)
{
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();
	const vector<BackGround*>& bg = GET_SINGLE(ObjectManager)->GetBackGround();
	bg[0]->Render(mdc, player[0]->GetDiffP1(), player[0]->GetDiffP2(), player[0]->GetTurn(), player[0]->GetDivide());
	player[0]->CRender(mdc);



	const vector<Tile*> tiles = GET_SINGLE(ObjectManager)->GetTile();
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Render(mdc);
	}


	const vector<Tile_P1*> tiles_p1 = GET_SINGLE(ObjectManager)->GetTile_P1();
	for (Tile_P1* tile : tiles_p1)
	{
		tile->Render(mdc);
	}


	const vector<Tile_P2*> tiles_p2 = GET_SINGLE(ObjectManager)->GetTile_P2();
	for (Tile_P2* tile : tiles_p2)
	{
		tile->Render(mdc);
	}



	const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();

	for (Missile* misile : missiles)
	{
		misile->Render(mdc);
	}



};