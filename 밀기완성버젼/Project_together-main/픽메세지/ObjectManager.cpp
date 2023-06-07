#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "BackGround.h"
#include "Tile_P1.h"
#include "Tile_P2.h"
#include "Tile.h"
#include "Tile_Moving.h"
#include "Tile_KnockBack.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Tile_KnockBack* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileKB.begin(), _vTileKB.end(), object);

	if (findit != _vTileKB.end())
		return;

	//////////////////////////////////////
	_vTileKB.push_back(object);

}

void ObjectManager::Add(Tile_Push* object)
{

	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_vTilePush.begin(), _vTilePush.end(), object);

	if (findit != _vTilePush.end())
		return;
	//////////////////////////////////////

	_vTilePush.push_back(object);


}

void ObjectManager::Add(Player* object)
{
	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_player.begin(), _player.end(), object);

	if (findit != _player.end())
		return;
	//////////////////////////////////////

	_player.push_back(object);
}

void ObjectManager::Add(BackGround* object)
{
	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_bg.begin(), _bg.end(), object);

	if (findit != _bg.end())
		return;
	//////////////////////////////////////

	_bg.push_back(object);
}

void ObjectManager::Add(Tile* object)
{

	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_vTile.begin(), _vTile.end(), object);

	if (findit != _vTile.end())
		return;
	//////////////////////////////////////

	_vTile.push_back(object);


}


void ObjectManager::Add(Missile* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vmissile.begin(), _vmissile.end(), object);

	if (findit != _vmissile.end())
		return;

	//////////////////////////////////////
	_vmissile.push_back(object);
}

void ObjectManager::Add(Tile_P1* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileP1.begin(), _vTileP1.end(), object);

	if (findit != _vTileP1.end())
		return;
	//////////////////////////////////////
	_vTileP1.push_back(object);
}

void ObjectManager::Add(Tile_P2* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileP2.begin(), _vTileP2.end(), object);

	if (findit != _vTileP2.end())
		return;
	//////////////////////////////////////
	_vTileP2.push_back(object);

}

void ObjectManager::Add(Tile_Moving* object)
{

	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileMove.begin(), _vTileMove.end(), object);

	if (findit != _vTileMove.end())
		return;
	//////////////////////////////////////
	_vTileMove.push_back(object);

}

void ObjectManager::Remove(Tile_KnockBack* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileKB.begin(), _vTileKB.end(), object);

	_vTileKB.erase(it, _vTileKB.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile_Push* object)
{

	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTilePush.begin(), _vTilePush.end(), object);

	_vTilePush.erase(it, _vTilePush.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;


}

void ObjectManager::Remove(Player* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_player.begin(), _player.end(), object);

	_player.erase(it, _player.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(BackGround* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_bg.begin(), _bg.end(), object);

	_bg.erase(it, _bg.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTile.begin(), _vTile.end(), object);

	_vTile.erase(it, _vTile.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;

}


void ObjectManager::Remove(Missile* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vmissile.begin(), _vmissile.end(), object);

	_vmissile.erase(it, _vmissile.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;

}


void ObjectManager::Remove(Tile_P1* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileP1.begin(), _vTileP1.end(), object);

	_vTileP1.erase(it, _vTileP1.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile_P2* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileP2.begin(), _vTileP2.end(), object);

	_vTileP2.erase(it, _vTileP2.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;


}

void ObjectManager::Remove(Tile_Moving* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileMove.begin(), _vTileMove.end(), object);

	_vTileMove.erase(it, _vTileMove.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;
}

void ObjectManager::Clear()
{
	//벡터내에 모든 메모리삭제
	std::for_each(_player.begin(), _player.end(), [=](Player* obj) {delete obj; });
	std::for_each(_bg.begin(), _bg.end(), [=](BackGround* obj) {delete obj; });
	std::for_each(_vTile.begin(), _vTile.end(), [=](Tile* obj) {delete obj; });
	std::for_each(_vTileP1.begin(), _vTileP1.end(), [=](Tile_P1* obj) {delete obj; });
	std::for_each(_vTileP2.begin(), _vTileP2.end(), [=](Tile_P2* obj) {delete obj; });
	std::for_each(_vTileMove.begin(), _vTileMove.end(), [=](Tile_Moving* obj) {delete obj; });
	std::for_each(_vmissile.begin(), _vmissile.end(), [=](Missile* obj) {delete obj; });
	std::for_each(_vTileKB.begin(), _vTileKB.end(), [=](Tile_KnockBack* obj) {delete obj; });


	//벡터 비우기
	_player.clear();
	_bg.clear();
	_vTile.clear();
	_vTileP1.clear();
	_vTileP2.clear();
	_vTileMove.clear();
	_vmissile.clear();
	_vTileKB.clear();

}
