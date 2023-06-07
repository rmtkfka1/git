#pragma once
#include "Object.h"
class Tile_P1 : public Object
{

public:

	Tile_P1();
	virtual ~Tile_P1() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;


private:
	HDC			mdc2;
	HBITMAP		hBitmap2;


	CImage      tile_img;

	Pos			_Renderpos{};		// ·»´õ¸µ ÁÂÇ¥
	WCHAR test[100];
};

