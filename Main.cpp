//======================================
//	3Dダンジョン メイン
//======================================
#include "Stage.h"
#include "UI.h"
#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
// 関数プロトタイプ
void game();
void DrawEnding();

int main()
{
    InitRand();

    int c;
    do {
        game();
        printf("もう一度(y/n)?");
        while (true) {
            c = GetKey();
            if (c == 'y' || c == 'n') {
                break;
            }
        }
    } while (c == 'y');
    return 0;
}

void game()
{
    Stage stage[1];
    InitializeStage(stage);

    while (true) {
        // 描画
        ClearScreen();
        Draw3D(stage);
        DrawMap(stage);
        DrawOperation(stage);
        // プレーヤ移動
        bool isEsc = MovePlayer(stage);
        if (isEsc) {
            break;
        }
        // ゴール?
        if (IsGoalPlayer(stage)) {
            // エンディング描画
            DrawEnding();
            WaitKey();
            break;
        }
    }
}

void DrawEnding()
{
    ClearScreen();
    printf(
        "　＊　＊　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ　＊　＊\n"
        "\n"
        "　あなたはついに　でんせつのまよけを　てにいれた！\n"
        "\n"
        "　しかし、くらくをともにした　「なかま」という\n"
        "かけがえのない　たからをてにした　あなたにとって、\n"
        "まよけのかがやきも　いろあせて　みえるのであった…\n"
        "\n"
        "　　　　　　　～　ＴＨＥ　ＥＮＤ　～\n"
        "\n");
}