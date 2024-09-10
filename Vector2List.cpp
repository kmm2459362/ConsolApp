//======================================
//	Vector2List
//======================================
#include "Vector2List.h"
#include <stdio.h>   // printf()
#include <stdlib.h>  // calloc(),free(),exit()
// 初期化
void InitializeVector2List(Vector2List* list, int size)
{
	list->array = (Vector2*)calloc(size, sizeof(Vector2));
	if (list->array == nullptr) {
		printf("calloc失敗\n");
		exit(1);
	}
	list->size = size;
	list->ptr = 0;
}
// 後始末
void FinalizeVector2List(Vector2List* list)
{
	free(list->array);
	list->size = 0;
	list->ptr = 0;
}
// リストに追加
void AddVector2List(Vector2List* list, Vector2 pos)
{
	if (list->ptr < list->size) {
		list->array[list->ptr++] = pos;
	}
}
// リスト[idx]を削除
void DelVector2List(Vector2List* list, int idx)
{
	if (idx < list->ptr) {
		while (idx + 1 < list->ptr) {
			list->array[idx] = list->array[idx + 1];
			idx++;
		}
		list->ptr--;
	}
}

// リストの要素数を得る
int GetCountVector2List(Vector2List* list)
{
	return list->ptr;
}
// リストの要素を得る
Vector2 GetVector2List(Vector2List* list, int idx)
{
	static Vector2 dummyPos = { -1,-1 };
	if (idx < list->ptr) {
		return list->array[idx];
	}
	return  dummyPos;
}
// リストをクリアする
void ClearVector2List(Vector2List* list)
{
	list->ptr = 0;
}
// リストをコピーする
void CopyVector2List(Vector2List* dst, Vector2List* src)
{
	ClearVector2List(dst);
	int count = GetCountVector2List(src);
	for (int i = 0; i < count; i++) {
		Vector2 pos = GetVector2List(src, i);
		AddVector2List(dst, pos);
	}
}
void PrintVector2List(Vector2List* list)
{
	printf("Vector2List(%d):", list->ptr);
	for (int i = 0; i < list->ptr; i++) {
		Vector2 pos = list->array[i];
		printf("(%d,%d)", pos.x, pos.y);
	}
	putchar('\n');
}