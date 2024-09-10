//======================================
//	3Dダンジョン UI
//======================================
#include "Stage.h"
#include "Character.h"
#include "Utility.h"
#include <stdio.h>
// 関数プロトタイプ
void MovePlayerForMap(Stage* stage, Key c);
void MovePlayerFor3D(Stage* stage, Key c);

bool MovePlayer(Stage* stage)
{
	Key c = GetKey();
	if (c == SPACE) {
		// stage->isForMapフラグを反転させてください
		// ★ここをコーディングしてください。
	}
	else if (c == ESC) {
		return true;
	}
	else {
		if (stage->isForMap) {
			MovePlayerForMap(stage, c);
		}
		else {
			MovePlayerFor3D(stage, c);
		}
	}
	return false;
}
// 操作法を描画
void DrawOperation(Stage* stage)
{
	puts("SPACE: change UI");
	puts("ESC : exit Game");
	if (stage->isForMap) {
		puts("↑:北へ向く/北へ前進");
		puts("←:西へ向く/西へ前進");
		puts("→:東へ向く/東へ前進");
		puts("↓:南へ向く/南へ前進");
	}
	else {
		puts("↑:前に進む");
		puts("←:左を向く");
		puts("→:右を向く");
		puts("↓:後ろを向く");
	}
}

// プレーヤ移動(ForMap)
void MovePlayerForMap(Stage* stage, Key c)
{
	Character* player = &stage->player;
	Direction d = DIR_MAX;
	switch (c) {
	case ARROW_UP:    d = DIR_NORTH; break;
	case ARROW_DOWN:  d = DIR_SOUTH; break;
	case ARROW_LEFT:  d = DIR_WEST; break;
	case ARROW_RIGHT: d = DIR_EAST; break;
	}  // ★ここが抜けていました
	if (d < DIR_MAX) {
		if (player->dir != d) {
			player->dir = d;
		}
		else {
			if (GetMazeWall(stage, player->pos, player->dir) == false) {
				Vector2 dir = GetDirVector2(d);
				Vector2 newPos = Vector2Add(player->pos, dir);
				if (IsInsideMaze(newPos)) {
					player->pos = newPos;
				}
			}
		}
	}
}

// プレーヤ移動(For3D)
void MovePlayerFor3D(Stage* stage, Key c)
{
	Character* player = &stage->player;
	switch (c) {
	case ARROW_UP:  // 前進
		if (GetMazeWall(stage, player->pos, player->dir) == false) {
			Vector2 dir = GetDirVector2(player->dir);
			Vector2 newPos = Vector2Add(player->pos, dir);
			if (IsInsideMaze(newPos)) {
				player->pos = newPos;
			}
		}
		break;
	case ARROW_DOWN: // 後ろを向く
		// ★ここをコーディングしてください
		// Characterの関数を利用します
		break;
	case ARROW_LEFT: // 左を向く
		// ★ここをコーディングしてください
		// Characterの関数を利用します
		break;
	case ARROW_RIGHT: // 右を向く
		// ★ここをコーディングしてください
		// Characterの関数を利用します
		break;
	}
}