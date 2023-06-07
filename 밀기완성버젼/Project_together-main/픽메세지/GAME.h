#pragma once

class GAME
{
public:
	DECLARE_SINGLE(GAME);

public:
	~GAME();
	void Init(HWND hwnd);
	void Update();
	void Render();

private:

	HWND hwnd;
	HDC hdc;
	//더블버퍼링
	RECT rt;
	HDC mdc;
	HBITMAP hbitmap;

};
