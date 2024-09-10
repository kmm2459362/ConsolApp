//======================================
//	3Dダンジョン  ステージ
//======================================
#include "Stage.h"
#include "UI.h"
#include "Vector2List.h"
#include "IntList.h"
#include "Location.h"
#include "Utility.h"
#include <stdio.h>
#include <assert.h>
// 関数プロトタイプ
static void GenerateMap(Stage* stage);
void DigWall(Stage* stage, Vector2 pos, Direction dir);
bool CanDigWall(Stage* stage, Vector2 pos, Direction dir);
void SetMazeWall(Stage* stage, Vector2 pos, Direction dir, bool value);
bool GetMazeWall(Stage* stage, Vector2 pos, Direction dir);
static void DrawMap_HorizontalWall(Stage* stage, int y, Direction dir);

// 初期化
void InitializeStage(Stage* stage)
{
	GenerateMap(stage);
	InitCharacter(&stage->player, { 0,0 }, DIR_NORTH);
	SetVector2(&stage->goal, GOAL_X, GOAL_Y);
	stage->isForMap = false;
}
// プレーヤがゴールしたか?
bool IsGoalPlayer(Stage* stage)
{
	// プレーヤの座標がゴールの座標と一致してか調べます
	// Vector2Equ()を使います
	// ★ここをコーディングしてください
}

// マップ生成
static void GenerateMap(Stage* stage)
{
	// Maze初期化(maze走査、全てのdirection[]をtrueに)
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			Vector2 pos = { x,y };
			for (int d = 0; d < DIR_MAX; d++) {
				SetMazeWall(stage, pos, (Direction)d, true);
			}
		}
	}

	Vector2 curPos = { 0,0 };
	Vector2List toDigWallPos[1];
	IntList canDigDirection[1];
	InitializeVector2List(toDigWallPos, MAZE_WIDTH * MAZE_HEIGHT);
	InitializeIntList(canDigDirection, DIR_MAX);
	AddVector2List(toDigWallPos, curPos);

	while (true) {
		// curPosの掘れる向きをリスティング
		ClearIntList(canDigDirection);
		for (int d = 0; d < DIR_MAX; d++) {
			if (CanDigWall(stage, curPos, (Direction)d)) {
				AddIntList(canDigDirection, d);
			}
		}

		int count = GetCountIntList(canDigDirection);
		if (count > 0) {
			// リストからランダムに選んで、掘る
			int idx = GetRand(count);
			Direction digDirection = (Direction)GetIntList(canDigDirection, idx);
			DigWall(stage, curPos, digDirection);
			// 掘った向きに進む
			Vector2 digVec = GetDirVector2(digDirection);
			curPos = Vector2Add(curPos, digVec);
			AddVector2List(toDigWallPos, curPos);
		}
		else {
			// 掘れる向きがないとき、
			DelVector2List(toDigWallPos, 0);
			if (GetCountVector2List(toDigWallPos) <= 0) {
				break;
			}
			curPos = GetVector2List(toDigWallPos, 0);
		}
	}
}
// マップを描画
void DrawMap(Stage* stage)
{
	Character* player = &stage->player;

	for (int y = 0; y < MAZE_HEIGHT; y++) {
		DrawMap_HorizontalWall(stage, y, DIR_NORTH);

		for (int x = 0; x < MAZE_WIDTH; x++) {
			Vector2 pos = { x,y };
			const char* floor = "　";
			if (Vector2Equ(pos, player->pos)) {
				static const char* directionAA[] = {
					"↑",  // DIR_NORTH
					"←",  // DIR_WEST
					"↓",  // DIR_SOUTH
					"→",  // DIR_EAST
				};
				floor = directionAA[player->dir];
			}
			else if (Vector2Equ(pos, stage->goal)) {
				floor = "Ｇ";
			}
			const char* west = GetMazeWall(stage, pos, DIR_WEST) ? "|" : " ";
			const char* east = GetMazeWall(stage, pos, DIR_EAST) ? "|" : " ";
			printf("%s%s%s", west, floor, east);
		}
		putchar('\n');

		DrawMap_HorizontalWall(stage, y, DIR_SOUTH);
	}
}
// DIR_NORTH/DIR_SOUTH の水平壁を描画
static void DrawMap_HorizontalWall(Stage* stage, int y, Direction dir)
{
	for (int x = 0; x < MAZE_WIDTH; x++) {
		const char* wall = GetMazeWall(stage, { x, y }, dir) ? "―" : "　";
		printf("+%s+", wall);
	}
	putchar('\n');
}

// 疑似3D 描画
void Draw3D(Stage* stage)
{
	char screen[] =
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n";
	// 
	//  プレーヤの周囲(A～E)について
	//	+--+--+--+
	//  |Ａ|Ｃ|Ｂ|
	//  +--+--+--+
	//  |Ｄ|↑|Ｅ|
	//  +--+--+--+
	Character* player = &stage->player;
	for (int i = 0; i < LOC_MAX; i++) {
		Vector2 loc = GetLocationVector2(player->dir, (Location)i);
		Vector2 pos = Vector2Add(player->pos, loc);
		if (IsInsideMaze(pos) == false) {
			continue;
		}

		for (int j = 0; j < DIR_MAX; j++) {
			// プレーヤから見た方向
			// ↑←↓→(0,1,2,3) をプレーヤ↑(0)　から見ると ↑←↓→(0,1,2,3)
			// ↑←↓→(0,1,2,3) をプレーヤ←(1)　から見ると →↑←↓(3,0,1,2)
			// ↑←↓→(0,1,2,3) をプレーヤ↓(2)　から見ると ↓→↑←(2,3,0,1) 
			// ↑←↓→(0,1,2,3) をプレーヤ→(3)　から見ると ←↓→↑(1,2,3,0)
			Direction dir = (Direction)((DIR_MAX + j - player->dir) % DIR_MAX);

			if (GetMazeWall(stage, pos, (Direction)j) == false) {
				continue;
			}
			const char* aa = GetLocationAA((Location)i, dir);
			if (aa == nullptr) {
				continue;
			}
			// aa[] を screen[]へ空白以外をコピーします。
			// ★ここをコーディングしてください。
			// 
		}
	}
	//
	// screen を描画
	//
	for (int i = 0; i < sizeof(screen) - 1; i++) {
		char c = screen[i];
		switch (c) {
		case ' ': printf("　"); break;
		case '#': printf("　"); break;
		case '_': printf("＿"); break;
		case '|': printf("｜"); break;
		case '/': printf("／"); break;
		case 'L': printf("＼"); break;
		case '\n':
			printf("%c", c);
			break;
		default:
			printf("%2x\n", c);
			assert(false);
			break;
		}
	}
}
// mazeのposをdir 方向に掘る
void DigWall(Stage* stage, Vector2 pos, Direction dir)
{
	// mazeの外ならなにもしない
	if (IsInsideMaze(pos) == false) {
		return;
	}
	SetMazeWall(stage, pos, dir, false);

	Vector2 dirVector2 = GetDirVector2(dir);
	Vector2 newPos = Vector2Add(pos, dirVector2);

	if (IsInsideMaze(newPos)) {
		// 北→南、西→東、南→北、東→西
		Direction dir2 = (Direction)((dir + 2) % DIR_MAX);
		SetMazeWall(stage, newPos, dir2, false);
	}
}
// mazeのposをdir方向に掘れるか?
bool CanDigWall(Stage* stage, Vector2 pos, Direction dir)
{
	Vector2 dirVector2 = GetDirVector2(dir);
	Vector2 nextPos = Vector2Add(pos, dirVector2);
	if (IsInsideMaze(nextPos) == false) {
		return false;
	}

	for (int d = 0; d < DIR_MAX; d++) {
		if (GetMazeWall(stage, nextPos, (Direction)d) == false) {
			return false;
		}
	}
	return true;
}
// mazeのposのdir セッター
void SetMazeWall(Stage* stage, Vector2 pos, Direction dir, bool value)
{
	// posとdir の範囲チェックを行って、okならvalueを代入します
	// ★ここをコーディングしてください。
}
// mazeのposのdir ゲッター
bool GetMazeWall(Stage* stage, Vector2 pos, Direction dir)
{
	// posとdir の範囲チェックを行って、okなら値を返します
	// そうでなければ falseを返します
	// ★ここをコーディングしてください。
}
// 座標がmaze内か?
bool IsInsideMaze(Vector2 pos)
{
	// pos.x が 0 ～ MAZE_WIDTH-1　かつ
	// pos.y が 0 ～ MAZE_HEIGHT-1 かを調べます
	// ★ここをコーディングしてください。
}