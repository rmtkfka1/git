#pragma once
#include "Scene.h"

class Player;
class BackGround;


class Stage1 : public Scene
{
public:
	DECLARE_SINGLE(Stage1);
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;


public:

};

