#pragma once//======================================
//	�R�}���hUI
//======================================
#ifndef __COMMAND_UI_H
#define __COMMAND_UI_H
#include "Command.h"
#include "TurnBattle.h"

// �v���[���̃R�}���h�擾
Command GetPlayerCommand(TurnBattle* btl);
// �G�̃R�}���h�擾
Command GetEnemyCommand();

#endif __COMMAND_UI_H

