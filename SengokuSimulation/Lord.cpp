//======================================
//	�퍑�V�~�����[�V����  ���
//======================================
#include "Lord.h"

typedef struct {
    const char* familyName;   // ��
    const char* firstName;    // ��
    const char* mapName;      // �}�b�v��̖��O
} LordName;

static LordName lordNames[LORD_MAX] = {
    {"�ɒB",    "�P�@", "�ɒB"},    // LORD_DATE        �ɒB�P�@
    {"�㐙",    "���M", "�㐙"},    // LORD_UESUGI      �㐙���M
    {"���c",    "�M��", "���c"},    // LORD_TAKEDA      ���c�M��
    {"�k��",    "����", "�k��"},    // LORD_HOJO        �k������
    {"����",    "�ƍN", "����"},    // LORD_TOKUGAWA    ����ƍN
    {"�D�c",    "�M��", "�D�c"},    // LORD_ODA         �D�c�M��
    {"����",    "�`��", "����"},    // LORD_ASHIKAGA    �����`��
    {"�ї�",    "���A", "�ї�"},    // LORD_MORI        �ї����A
    {"���@�䕔","���e", "���@"},    // LORD_CHOSOKABE   ���@�䕔���e
    {"����",    "�`�v", "����"},    // LORD_SIMAZU      ���Ë`�v
    {"�H��",    "�G�g", "�H��"},    // LORD_HASHIBA     �H�ďG�g
};

// ���̖����擾
const char* GetLordFirstName(LordId id)
{
    // id�� 0�`LORD_MAX-1 �ł��邱�Ƃ��`�F�b�N���Ă��������B
    // lordNames[id]�� firstName ��Ԃ��܂�
    // �͈͊O�Ȃ� "??"��Ԃ��܂�
    // ���������R�[�f�B���O���Ă��������B
    if (0 <= id && id < LORD_MAX)
    {
        return lordNames[id].familyName;
    }
    return "??";
}
// ���̐����擾
const char* GetLordFamilyName(LordId id)
{
    // id�� 0�`LORD_MAX-1 �ł��邱�Ƃ��`�F�b�N���Ă��������B
    // lordNames[id]�� familyName ��Ԃ��܂�
    // �͈͊O�Ȃ� "??"��Ԃ��܂�
    // ���������R�[�f�B���O���Ă��������B

    if (0 <= id && id < LORD_MAX)
    {
        return lordNames[id].familyName;
    }
    return "??";
}
// ���̃}�b�v��̖��O���擾
const char* GetLordMapName(LordId id)
{
    // id�� 0�`LORD_MAX-1 �ł��邱�Ƃ��`�F�b�N���Ă��������B
    // lordNames[id]�� mapName ��Ԃ��܂�
    // �͈͊O�Ȃ� "??"��Ԃ��܂�
    // ���������R�[�f�B���O���Ă��������B
    if (0 <= id && id < LORD_MAX)
    {
        return lordNames[id].familyName;
    }
    return "??";
}
