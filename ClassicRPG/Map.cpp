#pragma once
//======================================
//	�}�b�v
//======================================
#include "Map.h"
#include <assert.h>
// �搔�v���g�^�C�v
static bool isInMap(int x, int y);

MapArray mapField = {
        "~~~~~~~~~~~~~~~~",
        "~~MMMMM~~MMMM.~~",
        "~M...M.##..M...~",
        "~M.M.M.~~M.M.M.~",
        "~M.M...~~M...M.~",
        "~M.MMMM~~MMMM..~",
        "~M..MM.~~~~~~#~~",
        "~~M.M.~~~~~~~#~~",
        "~~M.MM~~~~BMM..~",
        "~~...MM~~M.MMM.~",
        "~...~~M~~M...M.~",
        "~..~~~K~~MMM.M.~",
        "~..~~~.~~M...M.~",
        "~......~~M.MM..~",
        "~~....~~~~....~~",
        "~~~~~~~~~~~~~~~~"
};
MapArray mapKingCastle = {
        "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H.........H.",
        ".H.HHH.HHH.H.",
        ".H.H0H.H1H.H.",
        ".H.........H.",
        ".HW.......WH.",
        ".HY.......YH.",
        "HHHHHH.HHHHHH",
        "H.H~~~#~~~H.H",
        "HHH~~~#~~~HHH",
        ".............."
};
MapArray mapBossCastle = {
       "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H....H....H.",
        ".H..WHHHW..H.",
        ".H..YH2HY..H.",
        ".H.........H.",
        ".H..W...W..H.",
        ".H..Y...Y..H.",
        ".H.........H.",
        "HHHHHH.HHHHHH",
        "H.H~~~#~~~H.H",
        "HHH~~~#~~~HHH",
        "~~~~~~#~~~~~~",
        "~~~~~~#~~~~~~",
        "............."
};

MapSpec specField = {
    &mapField,                // mapArray
    '~',                      // outData
    { MAP_NONE,0,0 },         // nextMap_Out
    { MAP_KING_CASTLE,6,12},  // nextMap_K
    { MAP_BOSS_CASTLE,6,15},  // nextMap_B
    true,                     // isBattleEncount
};

MapSpec specKingCastle = {
    &mapKingCastle,     // mapArray
    '.',                // outData
    { MAP_FIELD,6,12},  // nextMap_Out
    { MAP_NONE,0,0},    // nextMap_K
    { MAP_NONE,0,0},    // nexrMap_B
    false,              // isBattleEncount
};

MapSpec specBossCastle = {
    &mapBossCastle,     // mapArray
    '.',                // outData
    { MAP_FIELD,10,9},  // nextMap_Out
    { MAP_NONE,0,0},    // nextMap_K
    { MAP_NONE,0,0},    // nexrMap_B
    false,              // isBattleEncount
};
// id����}�b�v�X�y�b�N���擾
MapSpec* GetMapSpec(MapId id)
{
    static MapSpec* specs[] = {
        &specField,
        &specKingCastle,
        &specBossCastle,
    };
    const int specsSize = sizeof(specs) / sizeof(specs[0]);
    // ���������R�[�f�B���O���Ă��������B
    // id�� 0�`specsSize-1 �ł��邱�Ƃ�assert�Ŋm�F��
    // specs[id]��Ԃ��܂�
    assert(0 <= id && id < specsSize);
    return specs[id];
}
// �}�b�v�f�[�^���擾
char GetMapData(MapSpec* spec, int x, int y)
{
    // ���������R�[�f�B���O���Ă��������B
    // ���W���}�b�v�����m�F���܂�
    // space��array[y][x]���A�N�Z�X���āA'\0'�łȂ���΂����Ԃ��܂�
    // �}�b�v�O�܂��� '\0' �Ȃ� outOfMap�R�[�h��Ԃ��܂�
    if (isInMap(x, y)) {
        char c = (*spec->array)[y][x];
        if (c != '\0') {
            return c;
        }

    }
    return outOfMap;
}
// �}�b�v��AA(�A�X�L�[�A�[�g)���擾
const char* GetMapAA(char c)
{
    switch (c) {
    case '~':   return "�`";  // �C
    case '.':   return "�D";  // ���n
    case 'M':   return "�l";  // �R
    case '#':   return "��";  // ��
    case 'K':   return "��";  // ���l�̏�
    case 'B':   return "��";  // �����̏�
    case 'H':   return "��";  // ��
    case 'W':   return "��";  // ��
    case 'Y':   return "�x";  // �C��
    case '0':   return "��";  // ��
    case '1':   return "�P";  // �P
    case '2':   return "��";  // ����
    }
    assert(false);
    return "";
}
bool IsBattleEncount(MapSpec* spec)
{
    // ���������R�[�f�B���O���Ă�������
    // spec��isBattleEncount ��Ԃ��܂�
    return spec->isBattleEncount;
}

static bool isInMap(int x, int y)
{
    // ���������R�[�f�B���O���Ă�������
    //  x�� 0 �`MAP_WIDTH ���� y�� 0�`MAP_HEIGHT�𒲂ׂ܂�
    return 0 <= x && x < MAP_WIDTH && 0 <= y && y < MAP_HEIGHT;
}