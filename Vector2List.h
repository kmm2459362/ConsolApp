//======================================
//	Vector2List
//======================================
#ifndef __VECTOR2_LIST_H
#define __VECTOR2_LIST_H
#include "Vector2.h"
typedef struct {
	int size;        // 配列サイズ
	int ptr;         // 格納ポインタ
	Vector2* array;  // 配列
} Vector2List;

// 初期化
void InitializeVector2List(Vector2List* list, int size);
// 後始末
void FinalizeVector2List(Vector2List* list);
// リストに追加
void AddVector2List(Vector2List* list, Vector2 pos);
// リスト[idx]を削除
void DelVector2List(Vector2List* list, int idx);
// リストの要素数を得る
int GetCountVector2List(Vector2List* list);
// リストの要素を得る
Vector2 GetVector2List(Vector2List* list, int idx);
// リストをクリア
void ClearVector2List(Vector2List* list);
// リストをコピー
void CopyVector2List(Vector2List* dst, Vector2List* src);
// リストをプリントする
void PrintVector2List(Vector2List* list);
#endif //  __VECTOR2_LIST_H
