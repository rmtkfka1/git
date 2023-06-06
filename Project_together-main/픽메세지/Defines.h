#pragma once
#define DECLARE_SINGLE(classname)                   \
public:											    \
	classname(){}									\
													\
public:												\
													\
	static classname* GetInstance()					\
	{												\
		static classname s_Insatance;				\
		return &s_Insatance;						\
	}												

#define GET_SINGLE(classname) classname::GetInstance() 

#define WINDOW_WIDTH 1216
#define WINDOW_HEIGHT 639


#define MakeTile(X,Y) do {											     \
    Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();       \
    tile->SetPos(Pos(X, Y));											\
    tile->Init();														\
    GET_SINGLE(ObjectManager)->Add(tile);								\
} while(0)



#define MakeTile_P1(X,Y) do {											\
    Tile_P1* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P1>(); \
    tile->SetPos(Pos(X, Y));											\
    tile->Init();														\
    GET_SINGLE(ObjectManager)->Add(tile);								\
} while(0)


#define MakeTile_P2(X,Y) do {											\
    Tile_P2* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P2>(); \
    tile->SetPos(Pos(X, Y));											\
    tile->Init();														\
    GET_SINGLE(ObjectManager)->Add(tile);								\
} while(0)
          