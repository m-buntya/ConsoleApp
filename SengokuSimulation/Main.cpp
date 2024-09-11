//======================================
//	�퍑�V�~�����[�V���� ���C��
//======================================
#include "Stage.h"
#include "Lord.h"
#include "UI.h"
#include "Utility.h"
#include "Chronology.h"
#include <stdio.h>   // printf(),putchar()
#include <stdlib.h>
// �֐��v���g�^�C�v
static void game();
static void DrawHonnojiEvent(Stage* stage);
static void DrawGameOver(Stage* stage);
static void DrawEnding(Stage* stage);

int main()
{
    InitRand();

    int c;
    do {
        game();
        printf("������x(y/n)?");
        while (true) {
            c = GetKey();
            if (c == 'y' || c == 'n') {
                break;
            }
        }
    } while (c == 'y');
    return 0;
}

const int CHRONOLOGY_BUFF_SIZE = 1024;
const int START_YEAR = 1570;
extern Castle castles[];

static void game()
{
    Stage stage[1];
    Chronology chro[1];
    InitializeChronology(chro, CHRONOLOGY_BUFF_SIZE);
    InitializeStage(stage, castles, CASTLE_MAX, START_YEAR, chro);

    StartStage(stage);
    CastleId playerCastle = InputPlayerCastle(stage);
    SetPlayerLord(stage, playerCastle);
    IntroStage(stage, playerCastle);

    while (true) {
        // �^�[���̏��Ԃ��V���t��
        MakeTurnOrder(stage);
        for (int i = 0; i < stage->castlesSize; i++) {
            // �e��̃^�[�����s
            ExecTurn(stage, i);
            // �v���[���̕���?
            if (IsPlayerLose(stage)) {
                DrawGameOver(stage);
                goto exit;
            }
            // �v���[���̏���
            if (IsPlayerWin(stage)) {
                DrawEnding(stage);
                goto exit;
            }
        }
        // �N�z��
        NextYear(stage);
        // �u�{�\���̕ρv�C�x���g
        if (IsHonnojiEvent(stage)) {
            SetHonnojiEvent(stage);
            DrawHonnojiEvent(stage);
        }
    }
exit:
    FinalizeStage(stage);
    FinalizeChronology(chro);
}

static void DrawHonnojiEvent(Stage* stage)
{
    DrawScreen(stage, DM_Event, 0);
    printf(
        "���q���G�u�Ă��́@�{�\���Ɂ@����I\n"
        "\n"
        "���q���G���@�{�\���́@�D�c�M�����@���イ���������I\n"
        "\n"
        "�D�c�M���u���ЂɁ@����΂��c\n"
        "\n"
        "�D�c�M���́@�{�\���Ɂ@�Ђ��͂Ȃ��@�����������I\n"
        "\n"
        "�����A�H�ďG�g���@�R��̂��������Ł@���q���G���@�������A\n"
        "�D�c���́@���������́@�������@���񂾂����I\n");

    WaitKey();
}

static void DrawGameOver(Stage* stage)
{
    DrawScreen(stage, DM_GameOver, 0);
    // �N�\��\��
    PrintChronology(stage->chro);
    putchar('\n');
    printf("�f�`�l�d�@�n�u�d�q\n");
    WaitKey();
}

static void DrawEnding(Stage* stage)
{
    DrawScreen(stage, DM_Ending, 0);
    // �N�\��\��
    PrintChronology(stage->chro);
    int year = stage->year + 3;
    const char* name1 = GetLordFamilyName(stage, stage->playerLord);
    const char* name2 = GetLordFirstName(stage, stage->playerLord);
    printf("%d�˂�@ %s %s���@�������������傤����Ɂ@�ɂ񂺂���\n", year, name1, name2);
    printf("%d�˂�@%s%s���@%s�΂��ӂ��@�Ђ炭\n", year, name1, name2, name1);
    putchar('\n');
    printf("�s�g�d�@�d�m�c");
    WaitKey();
}
