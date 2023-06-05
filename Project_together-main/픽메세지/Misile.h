#pragma once

#pragma once
#include "Object.h"
class Missile : public Object
{

public:

	Missile();

	virtual ~Missile() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;

	void SetMotion(Bullet_Dir motion) { _motion = motion; }
	Bullet_Dir GetMotion() { return _motion; }

private:
	Bullet_Dir _motion;
	HDC			mdc2;
	HBITMAP		hBitmap2;

	CImage bullet_img;

	Pos _Renderpos;

};

