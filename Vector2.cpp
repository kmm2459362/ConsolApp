//======================================
//	2Dベクター
//======================================
#include "Vector2.h"

// ベクター加算(a+=b)
void AddVector2(Vector2* a, Vector2* b)
{
	a->x += b->x;
	a->y += b->y;
}

void SetVector2(Vector2* a, int x, int y)
{
	a->x = x;
	a->y = y;
}

Vector2 Vector2Add(Vector2 a, Vector2 b)
{
	int x = a.x + b.x;
	int y = a.y + b.y;
	return { x,y };
}
Vector2 Vector2Sub(Vector2 a, Vector2 b)
{
	int x = a.x - b.x;
	int y = a.y - b.y;
	return { x,y };
}
bool Vector2Equ(Vector2 a, Vector2 b)
{
	return a.x == b.x && a.y == b.y;
}
