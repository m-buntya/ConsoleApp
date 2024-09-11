#pragma once
//======================================
//	�퍑�V�~�����[�V����  UI
//======================================
#ifndef __UI_H
#define __UI_H
#include "Stage.h"
#include "Castle.h"
#include "Command.h"

// �v���[���̏����͂�����
CastleId InputPlayerCastle(Stage* stage);
// �v���[���^�[������͂�����
Command InputPlayerTurn(Stage* stage, Castle* castle, CastleId* outTarget, int* sendTroopCount);

#endif // __UI_H