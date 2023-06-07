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
#include "Tile_Moving.h"
#include "Tile_KnockBack.h"
#include "Tile_Push.h"
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

	//벽쪽추가
	{
		Tile* tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile2->SetPos(Pos(0, -1000));
		tile2->Init();
		tile2->SetSize(Pos(620, 3000));
		GET_SINGLE(ObjectManager)->Add(tile2);
	}


	{
		Tile* tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile2->SetPos(Pos(2600, 170));
		tile2->Init();
		tile2->SetSize(Pos(70, 40));
		GET_SINGLE(ObjectManager)->Add(tile2);
	}

	for (int i = 0; i < 5; ++i)
	{
		MakeTile(2600 + (i + 1) * 100, 70-(i*100));
	}


	//끝에티어나온거
	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(3320, -400));
		tile->Init();
		tile->SetSize(Pos(80, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	{

		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2600, -400));
		tile->Init();
		tile->SetSize(Pos(80, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}


	{

		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2450, -400));
		tile->Init();
		tile->SetSize(Pos(50, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2300, -520));
		tile->Init();
		tile->SetSize(Pos(50, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}


	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2200, 0));
		tile->Init();
		tile->SetSize(Pos(100, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	for (int i = 0; i < 6; ++i)
	{
		MakeTile(1400 + (i + 1) * 100, -520);
	}


	//============================ Tile_P1 만들기 ==============================//
	{

		MakeTile_P1(3200, -530);

		MakeTile_P1(3100, -530);

		MakeTile_P1(3000, -530);


		MakeTile_P1(2800, -530);


		MakeTile_P1(2750, -320);



	}
	//============================ Tile_P2 만들기 ==============================//
	{
		

	
	}

	//============================ Moving_Tile 만들기  ===========================//

	{
		Tile_Moving* moving_tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile->Init();
		moving_tile->_move_range = Pos(250, 250);
		moving_tile->SetPos(Pos(3200, 170));
		GET_SINGLE(ObjectManager)->Add(moving_tile);
	}

	{
		Tile_Moving* moving_tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile2->Init();
		moving_tile2->_move_range = Pos(250,250);
		moving_tile2->_DoyouWant_UP = false;
		moving_tile2->SetSize(Pos(50, 40));
		moving_tile2->SetPos(Pos(3000, 170));
		GET_SINGLE(ObjectManager)->Add(moving_tile2);
	}

	//============================ 넉백 타일 만들기 ==============================//
	{
		MakeTile_KnocBack(1600, 450);
	}

	//===============================Tile_Push(밀수있는 타일)만들기======================================//


	MakeTile_PUSH(1000, 440);
	MakeTile_PUSH(1000, 400);
	MakeTile_PUSH(1000, 360);
	MakeTile_PUSH(1000, 320);
	MakeTile_PUSH(1000, 280);



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

	const vector<Tile_Moving*> moving_tile = GET_SINGLE(ObjectManager)->GetTile_Moving();
	for (int i = 0; i < moving_tile.size(); ++i)
	{
		moving_tile[i]->Update();
	}

	const vector<Tile_KnockBack*> tiles_KnockBack = GET_SINGLE(ObjectManager)->GetKnockBack();
	for (int i = 0; i < tiles_KnockBack.size(); ++i)
	{
		tiles_KnockBack[i]->Update();
	}


	const vector<Tile_Push*> tile_push = GET_SINGLE(ObjectManager)->GetTilePush();
	for (int i = 0; i < tile_push.size(); ++i)
	{
		tile_push[i]->Update();
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


	const vector<Tile_Moving*> moving_tile = GET_SINGLE(ObjectManager)->GetTile_Moving();
	for (int i = 0; i < moving_tile.size(); ++i)
	{
		moving_tile[i]->Render(mdc);
	}

	const vector<Tile_KnockBack*> tiles_knockback = GET_SINGLE(ObjectManager)->GetKnockBack();
	for (Tile_KnockBack* tile : tiles_knockback)
	{
		tile->Render(mdc);
	}


	const vector<Tile_Push*> tile_push = GET_SINGLE(ObjectManager)->GetTilePush();
	for (int i = 0; i < tile_push.size(); ++i)
	{
		tile_push[i]->Render(mdc);
	}

};