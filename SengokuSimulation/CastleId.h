#pragma once
//======================================
//	�퍑�V�~�����[�V����  ��ID
//======================================
#ifndef __CASTLE_ID_H
#define __CASTLE_ID_H

typedef enum {
    CASTLE_YONEZAWA,        // �đ��
    CASTLE_KASUGAYAMA,      // �t���R��
    CASTLE_TSUTSUJIGASAKI,  // �U�P�����
    CASTLE_ODAWARA,         // ���c����
    CASTLE_OKAZAKI,         // �����
    CASTLE_GIFU,            // �򕌏�
    CASTLE_NIJO,            // �����
    CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
    CASTLE_OKO,             // ���L��
    CASTLE_UCHI,            // ����
    CASTLE_MAX,             // (��ނ̐�)
    CASTLE_NONE = -1,         // ���X�g�I�[
} CastleId;

#endif //  __CASTLE_ID_H
