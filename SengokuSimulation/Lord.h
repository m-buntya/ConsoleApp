#pragma once
//======================================
//	�퍑�V�~�����[�V����  ���
//======================================
#ifndef __LORD_H
#define __LORD_H

#include "LordId.h"

// ���̖����擾
const char* GetLordFirstName(LordId id);
// ���̐����擾
const char* GetLordFamilyName(LordId id);
// ���̃}�b�v��̖��O���擾
const char* GetLordMapName(LordId id);

#endif //  __LORD_H