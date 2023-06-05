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

	void Clear(); //����ȯ�Ǹ� �����Ҵ�� �޸𸮽ϳ����

	const vector<Player*>& GetPlayer() { return _player; } //�ܺ� CPP,������Ͽ��� ���Ͱ�������//
	const vector<BackGround*>& GetBackGround() { return _bg; } //�ܺ� CPP,������Ͽ��� ���Ͱ�������//
	const vector<Tile*>& GetTile() { return _vTile; } //�ܺ� CPP,������Ͽ��� ���Ͱ�������//
	const vector<Missile*>& GetMissile() { return _vmissile; } //�ܺ� CPP,������Ͽ��� ���Ͱ�������//


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

