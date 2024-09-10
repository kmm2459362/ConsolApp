//======================================
//	2Dベクター
//======================================
#ifndef __VECTOR2_H
#define __VECTOR2_H

typedef struct {
	int x;
	int y;
} Vector2;

// ベクター加算
void AddVector2(Vector2* a, Vector2* b);

// 2Dベクターの加算
Vector2 Vector2Add(Vector2 a, Vector2 b);
// 2Dベクターの減算
Vector2 Vector2Sub(Vector2 a, Vector2 b);
// 2Dベクターの等価?
bool Vector2Equ(Vector2 a, Vector2 b);
// ベックーセット
void SetVector2(Vector2* vec, int x, int y);

#endif // __VECTOR2_H
