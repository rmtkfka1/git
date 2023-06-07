#include "pch.h"
#include "Tile_KnockBack.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"


Tile_KnockBack::Tile_KnockBack() :Object(ObjectType::TILE)
{


}
Tile_KnockBack::~Tile_KnockBack()
{

}

void Tile_KnockBack::Init()
{
    tile_img.Load(L"리소스\\plant.png");

    size.x = tile_img.GetWidth();
    size.y = tile_img.GetHeight();
}

void Tile_KnockBack::Update()
{

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는
    Player* p = player[0];

    const vector<Tile_KnockBack*>& tiles_knockback = GET_SINGLE(ObjectManager)->GetKnockBack();   //벡터를 가져오는것


    for (int i = 0; i < tiles_knockback.size(); ++i)
    {
        RECT p_rectP1 = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
        RECT p_rectP2 = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
        RECT tile_rect = { tiles_knockback[i]->GetPos().x, tiles_knockback[i]->GetPos().y, tiles_knockback[i]->GetPos().x + tiles_knockback[i]->GetSize().x
            ,tiles_knockback[i]->GetPos().y + tiles_knockback[i]->GetSize().y };
        RECT intersect_rect;

        if (IntersectRect(&intersect_rect, &p_rectP1, &tile_rect)) {

            p->_KnocBackP1 = true;
            if (p->_motionP1 == Motion::RIGHT)
                p->_KnockPosP1.x = p->_posP1.x - 150.f;
            if (p->_motionP1 == Motion::LEFT)
                p->_KnockPosP1.x = p->_posP1.x + 150.f;
        }
        if (IntersectRect(&intersect_rect, &p_rectP2, &tile_rect)) {

            p->_KnocBackP2 = true;
            if (p->_motionP2 == Motion::RIGHT)
                p->_KnockPosP2.x = p->_posP2.x - 150.f;
            if (p->_motionP2 == Motion::LEFT)
                p->_KnockPosP2.x = p->_posP2.x + 150.f;
        }


    }

}

void Tile_KnockBack::Render(HDC mdc)
{
    mdc2 = CreateCompatibleDC(mdc);
    hBitmap2 = CreateCompatibleBitmap(mdc, tile_img.GetWidth(), tile_img.GetHeight());
    SelectObject(mdc2, (HBITMAP)hBitmap2);

    tile_img.Draw(mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight()
        , 0, 0, tile_img.GetWidth(), tile_img.GetHeight());

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

    Player* p = player[0];

    Pos diff = p->GetDiffP1();
    Pos diff2 = p->GetDiffP2();

    if (p->_turn == ObjectType::PLAYER1)            // 초점이 1일 때
        _Renderpos = _pos - diff;                // << player1일 때
    else if (p->_turn == ObjectType::PLAYER2)        // 초점이 2
        _Renderpos = _pos - diff2;                // << player2일 때

    TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x * 0.5, size.y * 0.5,
        mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));

    DeleteObject(hBitmap2);
    DeleteDC(mdc2);
}