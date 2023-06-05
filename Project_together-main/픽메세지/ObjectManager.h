#pragma once
#pragma once

class Object;
class Player;
class BackGround;
class Missile;
class Tile;
//class Player2;
//class Missile;
//class Foothold;

class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);

	~ObjectManager();

	void Add(Player* object);
	void Add(BackGround* object);
	void Add(Tile* object);
	void Add(Missile* object);


	void Remove(Player* object);
	void Remove(BackGround* object);
	void Remove(Tile* object);
	void Remove(Missile* object);

	void Clear(); //씬전환되면 동적할당된 메모리싹날라기

	const vector<Player*>& GetPlayer() { return _player; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<BackGround*>& GetBackGround() { return _bg; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile*>& GetTile() { return _vTile; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Missile*>& GetMissile() { return _vmissile; } //외부 CPP,헤더파일에서 벡터가져오기//


	template<typename T>
	T* CreateObject()
	{
		T* object = new T();


		return object;
	}

private:

	vector<Player*> _player;
	vector<BackGround*> _bg;
	vector<Tile*> _vTile;
	vector<Missile*> _vmissile;
};

