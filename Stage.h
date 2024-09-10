//======================================
//	3Dダンジョン  ステージ
//======================================
#ifndef __STAGE_H
#define __STAGE_H
#include "Character.h"
#include "Vector2.h"
#include "Direction.h"

const int MAZE_WIDTH = 8;
const int MAZE_HEIGHT = 8;
const int GOAL_X = MAZE_WIDTH - 1;
const int GOAL_Y = MAZE_HEIGHT - 1;

typedef struct {
	bool walls[DIR_MAX];
} TILE;

typedef struct {
	TILE maze[MAZE_HEIGHT][MAZE_WIDTH];
	Character player;
	Vector2 goal;
	bool isForMap;   // UI forMap or for3D
} Stage;

// ステージ初期化
void InitializeStage(Stage* stage);
// 3D描画
void Draw3D(Stage* stage);
// 迷路マップ描画
void DrawMap(Stage* stage);
// プレーヤがゴールしたか?
bool IsGoalPlayer(Stage* stage);
// 指定位置の指定方向の壁セット
void SetMazeWall(Stage* stage, Vector2 pos, Direction dir, bool value);
// 指定位置の指定方向は壁か?
bool GetMazeWall(Stage* stage, Vector2 pos, Direction dir);
// 位置は迷路内?
bool IsInsideMaze(Vector2 pos);

#endif //  __STAGE_H