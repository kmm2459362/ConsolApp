//======================================
//	3Dダンジョン ディレクション(方向)
//======================================
#include "Direction.h"
#include <assert.h>

// ４方向のベクター取得
Vector2 GetDirVector2(Direction d)
{
	static Vector2 dirVector2[] = {
		{ 0,-1},  //DIR_NORTH
		{-1, 0},  //DIR_WEST
		{ 0, 1},  //DIR_SOUTH,
		{ 1, 0},  //DIR_EAST,
	};
	assert(0 <= d && d < DIR_MAX);
	return dirVector2[d];
}

// ディレクション加算
Direction DirectionAdd(Direction dir, int add)
{
	// dir に add(1,2,-1)を加算したあと、
	// 0 ～ DIR_MAX-1 の範囲内に収めます
	// ★ここをコーディングしてください
	//
}
// ディレクション範囲チェック
bool IsInDirection(Direction d)
{
	// dが 0 ～ DIR_MAX-1 か調べます
	// ★ここをコーディングしてください
}
