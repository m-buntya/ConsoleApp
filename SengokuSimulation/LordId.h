#pragma once
//======================================
//	�퍑�V�~�����[�V����  ���ID
//======================================
#ifndef __LORD_ID_H
#define __LORD_ID_H

typedef enum {
    LORD_DATE,      // �ɒB�P�@
    LORD_UESUGI,    // �㐙���M
    LORD_TAKEDA,    // ���c�M��
    LORD_HOJO,      // �k������
    LORD_TOKUGAWA,  // ����ƍN
    LORD_ODA,       // �D�c�M��
    LORD_ASHIKAGA,  // �����`��
    LORD_MORI,      // �ї����A
    LORD_CHOSOKABE, // ���@�䕔���e
    LORD_SIMAZU,    // ���Ë`�v
    LORD_HASHIBA,   // �H�ďG�g
    LORD_MAX,       // (��ނ̐�)
    LORD_NONE = -1,
} LordId;

#endif //  __LORD_ID_H
