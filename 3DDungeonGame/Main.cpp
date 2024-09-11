//======================================
//	3D�_���W���� ���C��
//======================================
#include "Stage.h"
#include "UI.h"
#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
// �֐��v���g�^�C�v
void game();
void DrawEnding();

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

void game()
{
    Stage stage[1];
    InitializeStage(stage);

    while (true) {
        // �`��
        ClearScreen();
        Draw3D(stage);
        DrawMap(stage);
        DrawOperation(stage);
        // �v���[���ړ�
        bool isEsc = MovePlayer(stage);
        if (isEsc) {
            break;
        }
        // �S�[��?
        if (IsGoalPlayer(stage)) {
            // �G���f�B���O�`��
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
        "�@���@���@�b�n�m�f�q�`�s�t�k�`�s�h�n�m�r�@���@��\n"
        "\n"
        "�@���Ȃ��͂��Ɂ@�ł񂹂̂܂悯���@�Ăɂ��ꂽ�I\n"
        "\n"
        "�@�������A���炭���Ƃ��ɂ����@�u�Ȃ��܁v�Ƃ���\n"
        "���������̂Ȃ��@��������Ăɂ����@���Ȃ��ɂƂ��āA\n"
        "�܂悯�̂����₫���@���날���ā@�݂���̂ł������c\n"
        "\n"
        "�@�@�@�@�@�@�@�`�@�s�g�d�@�d�m�c�@�`\n"
        "\n");
}