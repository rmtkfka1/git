#include "pch.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"



Tile::Tile() :Object(ObjectType::TILE)
{

}


Tile::~Tile()
{

}

void Tile::Init()
{
    tile_img.Load(L"리소스\\BasicGreen.png");

    size.x = 164;
    size.y = 64;
}

void Tile::Update()
{
    //================================================PLAYER1 타일 충돌처리 //////////////////////////////////////////////////////////////
    {

        const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

        Player* p = player[0];

        const vector<Tile*>& tiles = GET_SINGLE(ObjectManager)->GetTile();   //벡터를 가져오는것

        for (int i = 0; i < tiles.size(); ++i)
        {
            RECT p_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
            RECT tile_rect = { tiles[i]->GetPos().x, tiles[i]->GetPos().y, tiles[i]->GetPos().x + tiles[i]->GetSize().x
                ,tiles[i]->GetPos().y + tiles[i]->GetSize().y };
            RECT intersect_rect;

            if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
            {
                float GapW = intersect_rect.right - intersect_rect.left;
                float GAPH = intersect_rect.bottom - intersect_rect.top;

                if (GapW > GAPH)
                {

                    if (intersect_rect.top == tile_rect.top)
                    {
                        p->_posP1.y -= GAPH;
                    }

                    else if (intersect_rect.bottom == tile_rect.bottom)
                    {
                        p->_posP1.y += GAPH;
                    }
                }

                else
                {
                    if (intersect_rect.left == tile_rect.left)
                    {
                        p->_posP1.x = p->_posP1.x - GapW;
                    }

                    else if (intersect_rect.right == tile_rect.right)
                    {
                        p->_posP1.x = p->_posP1.x + GapW;

                    }
                }


                if (!p->rand1) {
                    p->rand1 = true;
                }

                std::thread resetFireThread([p]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
                    p->rand1 = false;
                    });

                resetFireThread.detach();

            }
        }

    }

    //================================================PLAYER2 타일 충돌처리 //////////////////////////////////////////////////////////////
    {

        const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

        Player* p = player[0];

        const vector<Tile*>& tiles = GET_SINGLE(ObjectManager)->GetTile();   //벡터를 가져오는것

        for (int i = 0; i < tiles.size(); ++i)
        {
            RECT p_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
            RECT tile_rect = { tiles[i]->GetPos().x, tiles[i]->GetPos().y, tiles[i]->GetPos().x + tiles[i]->GetSize().x
                ,tiles[i]->GetPos().y + tiles[i]->GetSize().y };
            RECT intersect_rect;

            if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
            {
                float GapW = intersect_rect.right - intersect_rect.left;
                float GAPH = intersect_rect.bottom - intersect_rect.top;

                if (GapW > GAPH)
                {

                    if (intersect_rect.top == tile_rect.top)
                    {
                        p->_posP2.y -= GAPH;
                    }

                    else if (intersect_rect.bottom == tile_rect.bottom)
                    {
                        p->_posP2.y += GAPH;
                    }
                }

                else
                {
                    if (intersect_rect.left == tile_rect.left)
                    {
                        p->_posP2.x = p->_posP2.x - GapW;
                    }

                    else if (intersect_rect.right == tile_rect.right)
                    {
                        p->_posP2.x = p->_posP2.x + GapW;

                    }
                }

                if (!p->rand2) {
                    p->rand2 = true;
                }

                std::thread resetFireThread([p]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    p->rand2 = false;
                    });

                resetFireThread.detach();
            }
        }

    }


}

void Tile::Render(HDC mdc)
{
    mdc2 = CreateCompatibleDC(mdc);
    hBitmap2 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(mdc2, (HBITMAP)hBitmap2);


    tile_img.Draw(mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight()
        , 0, 0, tile_img.GetWidth(), tile_img.GetHeight());

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

    Player* p = player[0];

    Pos diff = p->GetDiffP1();
    Pos diff2 = p->GetDiffP2();

    if (p->_turn == ObjectType::PLAYER1)            // 초점이 1일 때
        _CRenderposP1 = _pos - diff;                // << player1일 때
    else if (p->_turn == ObjectType::PLAYER2)        // 초점이 2
        _CRenderposP1 = _pos - diff2;                // << player2일 때

    TransparentBlt(mdc, _CRenderposP1.x, _CRenderposP1.y, tile_img.GetWidth(), tile_img.GetHeight(),
        mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(100, 100, 100));

    DeleteObject(hBitmap2);
    DeleteDC(mdc2);
}