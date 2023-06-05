#include "pch.h"
#include "Stage1.h"
#include "TimeManager.h"
#include "BackGround.h"
#include "KeyManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Misile.h"
#include "Tile.h"

Stage1::~Stage1()
{

}

void Stage1::Init()
{

	BackGround* bg = GET_SINGLE(ObjectManager)->CreateObject<BackGround>();
	bg->Init();
	GET_SINGLE(ObjectManager)->Add(bg); 


	Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
	tile->SetPos(Pos(800, 400));
	tile->Init();
	GET_SINGLE(ObjectManager)->Add(tile);


	Tile* tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
	tile2->SetPos(Pos(900, 300));
	tile2->Init();
	GET_SINGLE(ObjectManager)->Add(tile2);

	Tile* tile3 = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
	tile3->SetPos(Pos(1100, 200));
	tile3->Init();
	GET_SINGLE(ObjectManager)->Add(tile3);



	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	GET_SINGLE(ObjectManager)->Add(player); 
	player->Init(bg);





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



}


void Stage1::Render(HDC mdc)
{
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();
	const vector<BackGround*>& bg = GET_SINGLE(ObjectManager)->GetBackGround();
	bg[0]->Render(mdc, player[0]->GetDiffP1(), player[0]->GetDiffP2(), player[0]->GetTurn(), player[0]->GetDivide());
	player[0]->CRender(mdc);


	const vector<Tile*> tiles = GET_SINGLE(ObjectManager)->GetTile();

	for (Tile* tile : tiles)
	{
		tile->Render(mdc);
	}

	const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();

	for (Missile* misile : missiles)
	{
		misile->Render(mdc);
	}

	

}