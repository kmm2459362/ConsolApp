//======================================
//	ロケーション
//======================================
#include "Direction.h"
#include "Location.h"
#include <assert.h>

static Vector2 locations[DIR_MAX][LOC_MAX] = {
	// DIR_NORTH
	{            //                            x:-1 + 0 + 1
		{-1,-1}, // LOC_FRONT_LEFT  左前(A)     +--+--+--+
		{ 1,-1}, // LOC_FRONT_RIGHT 右前(B)     |Ａ|Ｃ|Ｂ|-1 
		{ 0,-1}, // LOC_FRONT       前(C)       +--+--+--+
		{-1, 0}, // LOC_LEFT        左(D)       |Ｄ|↑|Ｅ|+0
		{ 1, 0}, // LOC_RIGHT       右(E)       +--+--+--+
		{ 0, 0}, // LOC_CENTER      中心        |　|　|　|+1
		//                             +--+--+--+
},
// DIR_WEST
{            //                            x:-1 + 0 + 1
	{-1, 1}, // LOC_FRONT_LEFT  左前(A)     +--+--+--+
	{-1,-1}, // LOC_FRONT_RIGHT 右前(B)     |Ｂ|Ｅ|　|-1 
	{-1, 0}, // LOC_FRONT       前(C)       +--+--+--+
	{ 0,+1}, // LOC_LEFT        左(D)       |Ｃ|←|　|+0
	{ 0,-1}, // LOC_RIGHT       右(E)       +--+--+--+
	{ 0, 0}, // LOC_CENTER      中心        |Ａ|Ｄ|　|+1
	//                             +--+--+--+
},
// DIR_SOUTH
{            //                            x:-1 + 0 + 1
	{ 1, 1}, // LOC_FRONT_LEFT  左前(A)     +--+--+--+
	{-1, 1}, // LOC_FRONT_RIGHT 右前(B)     |　|　|　|-1 
	{ 0, 1}, // LOC_FRONT       前(C)       +--+--+--+
	{ 1, 0}, // LOC_LEFT        左(D)       |Ｅ|↓|Ｄ|+0
	{-1, 0}, // LOC_RIGHT       右(E)       +--+--+--+
	{ 0, 0}, // LOC_CENTER      中心        |Ｂ|Ｃ|Ａ|+1
	//                             +--+--+--+
},
// DIR_EAST
{            //                            x:-1 + 0 + 1
	{ 1,-1}, // LOC_FRONT_LEFT  左前(A)     +--+--+--+
	{ 1, 1}, // LOC_FRONT_RIGHT 右前(B)     |　|Ｄ|Ａ|-1 
	{ 1, 0}, // LOC_FRONT       前(C)       +--+--+--+
	{ 0,-1}, // LOC_LEFT        左(D)       |　|→|Ｃ|+0
	{ 0, 1}, // LOC_RIGHT       右(E)       +--+--+--+
	{ 0, 0}, // LOC_CENTER      中心        |　|Ｅ|Ｂ|+1
	//                             +--+--+--+
},
};
// 方向とロケーションから、オフセットベクター取得
Vector2 GetLocationVector2(Direction dir, Location loc)
{
	assert(IsInDirection(dir));
	assert(IsInLocation(loc));
	return locations[dir][loc];
}

// [5-2]基準となるアスキーアートを宣言する
// +..+==+..+
// .  |  |  .
// +..+..+..+
// .  |↑|  .
// +..+..+..+
static const char* all =
"L       /\n"
"#L     /#\n"
"#|L _ /|#\n"
"#|#|#|#|#\n"
"#|#|_|#|#\n"
"#|/   L|#\n"
"#/     L#\n"
"/       L\n";

// [5-3]左前方前の壁のアスキーアートを宣言する
// +==+..+..+ (この壁を描画)
// .  .  .  .
// +..+..+..+
// .  .↑.  .
// +..+..+..+
static const char* frontLeftNorth =
"         \n"
"         \n"
"  _      \n"
" |#|     \n"
" |_|     \n"
"         \n"
"         \n"
"         \n";

// [5-4]右前方前の壁のアスキーアートを宣言する
// +..+..+==+ (この壁を描画)
// .  .  .  .
// +..+..+..+
// .  .↑.  .
// +..+..+..+
static const char* frontRightNorth =
"         \n"
"         \n"
"      _  \n"
"     |#| \n"
"     |_| \n"
"         \n"
"         \n"
"         \n";

// [5-5]前方前の壁のアスキーアートを宣言する
// +..+==+..+ (この壁を描画)
// .  .  .  .
// +..+..+..+
// .  .↑.  .
// +..+..+..+
static const char* frontNorth =
"         \n"
"         \n"
"    _    \n"
"   |#|   \n"
"   |_|   \n"
"         \n"
"         \n"
"         \n";

// [5-6]前方左の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  |  .  . (この壁を描画)
// +..+..+..+
// .  .↑.  .
// +..+..+..+
static const char* frontWest =
"         \n"
"         \n"
" |L      \n"
" |#|     \n"
" |#|     \n"
" |/      \n"
"         \n"
"         \n";

// [5-7]前方右の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  .  |  . (この壁を描画)
// +..+..+..+
// .  .↑.  .
// +..+..+..+
static const char* frontEast =
"         \n"
"         \n"
"      /| \n"
"     |#| \n"
"     |#| \n"
"      L| \n"
"         \n"
"         \n";

// [5-8]左方前の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  .  .  .
// +==+..+..+ (この壁を描画)
// .  .↑.  .
// +..+..+..+
static const char* leftNorth =
"         \n"
"_        \n"
"#|       \n"
"#|       \n"
"#|       \n"
"_|       \n"
"         \n"
"         \n";

// [5-9]右方前の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  .  .  .
// +..+..+==+ (この壁を描画)
// .  .↑.  .
// +..+..+..+
static const char* rightNorth =
"         \n"
"        _\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |_\n"
"         \n"
"         \n";

// [5-10]前の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  .  .  .
// +..+==+..+ (この壁を描画)
// .  .↑.  .
// +..+..+..+
static const char* north =
"         \n"
"  _____  \n"
" |#####| \n"
" |#####| \n"
" |#####| \n"
" |_____| \n"
"         \n"
"         \n";

// [5-11]左の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  .  .  .
// +..+..+..+
// .  |↑.  . (この壁を描画)
// +..+..+..+
static const char* west =
"L        \n"
"#L       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#/       \n"
"/        \n";

// [5-12]右の壁のアスキーアートを宣言する
// +..+..+..+ 
// .  .  .  .
// +..+..+..+
// .  .↑|  . (この壁を描画)
// +..+..+..+
static const char* east =
"        /\n"
"       /#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       L#\n"
"        L\n";

const char* aaTable[LOC_MAX][DIR_MAX] =
{
	// LOC_FRONT_LEFT 左前
	{
		frontLeftNorth,  // DIR_NORTH(前方)
		nullptr,         // DIR_WEST (左方)
		nullptr,         // DIR_SOUTH(後方)
		nullptr,         // DIR_EAST (右方)
	},
	// LOC_FRONT_RIGHT 右前
	{
		frontRightNorth, // DIR_NORTH(前方)
		nullptr,         // DIR_WEST (左方)
		nullptr,         // DIR_SOUTH(後方)
		nullptr,         // DIR_EAST (右方)
	},
	// LOC_FRONT
	{
		frontNorth,      // DIR_NORTH(前方)
		frontWest,       // DIR_WEST (左方)
		nullptr,         // DIR_SOUTH(後方)
		frontEast,       // DIR_EAST (右方)
	},
	// LOC_LEFT
	{
		leftNorth,       // DIR_NORTH(前方)
		nullptr,         // DIR_WEST (左方)
		nullptr,         // DIR_SOUTH(後方)
		nullptr,         // DIR_EAST (右方)
	},
	// LOC_RIGHT
	{
		rightNorth,      // DIR_NORTH(前方)
		nullptr,         // DIR_WEST (左方)
		nullptr,         // DIR_SOUTH(後方)
		nullptr,         // DIR_EAST (右方)
	},
	// LOC_CENTER
	{
		north,          // DIR_NORTH(前方)
		west,           // DIR_WEST (左方)
		nullptr,        // DIR_SOUTH(後方)
		east,           // DIR_EAST (右方)
	},
};
// 方向とロケーションから、アスキーアート文字列を取得
const char* GetLocationAA(Location loc, Direction dir)
{
	assert(IsInDirection(dir));
	assert(IsInLocation(loc));
	return aaTable[loc][dir];
}
// ロケーション範囲チェック
bool IsInLocation(Location loc)
{
	// loc が 0 ～ LOC_MAX-1 かをチェックします
	// ★ここをコーディングしてください
}