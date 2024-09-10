//======================================
//	ユーティリティ
//======================================
#ifndef __UTILITY_H
#define __UTILITY_H

extern const char* EscBLACK;
extern const char* EscRED;
extern const char* EscGREEN;
extern const char* EscYELLOW;
extern const char* EscBLUE;
extern const char* EscMAZENTA;
extern const char* EscCYAN;
extern const char* EscWHITE;
extern const char* EscDEFAULT;

extern const char* EscBgBLACK;
extern const char* EscBgRED;
extern const char* EscBgGREEN;
extern const char* EscBgYELLOW;
extern const char* EscBgBLUE;
extern const char* EscBgMAZENTA;
extern const char* EscBgCYAN;
extern const char* EscBgWHITE;
extern const char* EscBgDEFAULT;

enum Key {
	ARROW_UP = 0xe048,
	ARROW_LEFT = 0xe04b,
	ARROW_DOWN = 0xe050,
	ARROW_RIGHT = 0xe04d,
	DECIDE = 0x0d,
	ESC = 0x1b,
	SPACE = 0x20,
};
// 乱数初期化
void InitRand();
// 0～max-1 の一様乱数を得る
int GetRand(int max);
// キー入力を待つ
void WaitKey();
// キー入力取得
Key GetKey();
// キー入力ありか?
bool KeyAvailable();
// スクリーン消去
void ClearScreen();
// カーソル位置セット
void PrintCursor(int curx, int cury);
// カーソル保存
void SaveCursor();
// カーソル復元
void RestoreCursor();
// 時間待ち(m秒)
void Sleep_mSec(int mSec);

#endif // __UTILITY_H