#pragma once
#include "Object.h"

class Tile : public Object
{

public:

	Tile();
	virtual ~Tile() override;
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
