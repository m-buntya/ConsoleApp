//======================================
//	�h�b�g�C�[�g�Q�[���@Character
//======================================
#include "Character.h"
#include "Vector2.h"

// �L�����N�^�[������
void InitCharacter(Character* ch, Chara id, Vector2 initPos)
{
	ch->id = id;
	ch->pos = initPos;
	ch->lastPos = initPos;
	//
	// ���������R�[�f�B���O���Ă�������
	// id,initPos �� ch�̃����o�[������������
	// ch->lastPos �� initPos �����Ă���
	//
}

// �L�����N�^�[�ړ�
void MoveCharacter(Character* ch, Vector2 newPos)
{
	ch->lastPos = ch->pos;
	ch->pos = newPos;
	//
	// ���������R�[�f�B���O���Ă�������
	// ���݈ʒu�� lastPos �ɓ����
	// ���݈ʒu�� newPos�������
	//
}
// �L�����N�^�[�̌����x�N�^�[���擾����
Vector2 GetCharacterDir(Character* ch)
{
	//
	// �P����  pos-lastPos ����ƁA���[�v�n�_�Ńo�O��
	//
	int x = ch->pos.x - ch->lastPos.x;
	if (x < -1 || 1 < x) {
		// �E�[�����[�A�܂��� �E�[�����[
		x = (ch->pos.x == 0) ? +1 : -1;
	}
	int y = ch->pos.y - ch->lastPos.y;
	if (y < -1 || 1 < x) {
		// ���[����[�A�܂��́A���[����[
		y = (ch->pos.y == 0) ? +1 : -1;
	}
	return { x,y };
}