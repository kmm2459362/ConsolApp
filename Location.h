//======================================
//	3Dダンジョン ロケーション
//======================================
#ifndef __LOCATION_H
#define __LOCATION_H

#include "Direction.h"
#include "Vector2.h"

// プレーヤからの相対位置
typedef enum {
	LOC_FRONT_LEFT,  // 左前
	LOC_FRONT_RIGHT, // 右前
	LOC_FRONT,       // 前
	LOC_LEFT,        // 左
	LOC_RIGHT,       // 右
	LOC_CENTER,      // 中心
	LOC_MAX,
} Location;

// 方向とロケーションから、オフセットベクター取得
Vector2 GetLocationVector2(Direction dir, Location loc);
// 方向とロケーションから、アスキーアート文字列を取得
const char* GetLocationAA(Location loc, Direction dir);
// ロケーション範囲チェック
bool IsInLocation(Location loc);

#endif // __LOCATION_H