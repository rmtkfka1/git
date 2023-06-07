#pragma once

class KeyManager
{
	DECLARE_SINGLE(KeyManager);

public:
	void Init(HWND hwnd);
	void Update();

	//누르고있을때
	bool Getbutton(KeyType key) { return GetState(key) == KeyState::PRESS; }

	//맨처음 눌렀을때
	bool GetbuttonDown(KeyType key) { return GetState(key) == KeyState::DOWN; }

	//맨처음 눌렀다가 땔대
	bool GetbuttonUp(KeyType key) { return GetState(key) == KeyState::UP; }

	POINT GetMousePos() { return _mousePos; }
private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }


	HWND _hwnd = 0;
	vector<KeyState> _states;
	POINT _mousePos = { 0,0 };


};
