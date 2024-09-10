//====================================
//	3Dダンジョン  キャラクタ
//======================================
#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "Vector2.h"
#include "Direction.h"

typedef struct {
	Vector2 pos;      // 座標
	Direction dir;    // 向いている方位
} Character;

// キャラ初期化
void InitCharacter(Character* ch, Vector2 pos, Direction dir);
// 後ろを向く
void TurnBackCharacter(Character* ch);
// 左を向く
void TurnLeftCharacter(Character* ch);
// 右を向く
void TurnRightCharacter(Character* ch);

#endif __CHARACTER_H
