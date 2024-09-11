//======================================
//	���P�[�V����
//======================================
#include "Direction.h"
#include "Location.h"
#include <assert.h>

static Vector2 locations[DIR_MAX][LOC_MAX] = {
	// DIR_NORTH
	{            //                            x:-1 + 0 + 1
		{-1,-1}, // LOC_FRONT_LEFT  ���O(A)     +--+--+--+
		{ 1,-1}, // LOC_FRONT_RIGHT �E�O(B)     |�`|�b|�a|-1 
		{ 0,-1}, // LOC_FRONT       �O(C)       +--+--+--+
		{-1, 0}, // LOC_LEFT        ��(D)       |�c|��|�d|+0
		{ 1, 0}, // LOC_RIGHT       �E(E)       +--+--+--+
		{ 0, 0}, // LOC_CENTER      ���S        |�@|�@|�@|+1
		//                             +--+--+--+
},
// DIR_WEST
{            //                            x:-1 + 0 + 1
	{-1, 1}, // LOC_FRONT_LEFT  ���O(A)     +--+--+--+
	{-1,-1}, // LOC_FRONT_RIGHT �E�O(B)     |�a|�d|�@|-1 
	{-1, 0}, // LOC_FRONT       �O(C)       +--+--+--+
	{ 0,+1}, // LOC_LEFT        ��(D)       |�b|��|�@|+0
	{ 0,-1}, // LOC_RIGHT       �E(E)       +--+--+--+
	{ 0, 0}, // LOC_CENTER      ���S        |�`|�c|�@|+1
	//                             +--+--+--+
},
// DIR_SOUTH
{            //                            x:-1 + 0 + 1
	{ 1, 1}, // LOC_FRONT_LEFT  ���O(A)     +--+--+--+
	{-1, 1}, // LOC_FRONT_RIGHT �E�O(B)     |�@|�@|�@|-1 
	{ 0, 1}, // LOC_FRONT       �O(C)       +--+--+--+
	{ 1, 0}, // LOC_LEFT        ��(D)       |�d|��|�c|+0
	{-1, 0}, // LOC_RIGHT       �E(E)       +--+--+--+
	{ 0, 0}, // LOC_CENTER      ���S        |�a|�b|�`|+1
	//                             +--+--+--+
},
// DIR_EAST
{            //                            x:-1 + 0 + 1
	{ 1,-1}, // LOC_FRONT_LEFT  ���O(A)     +--+--+--+
	{ 1, 1}, // LOC_FRONT_RIGHT �E�O(B)     |�@|�c|�`|-1 
	{ 1, 0}, // LOC_FRONT       �O(C)       +--+--+--+
	{ 0,-1}, // LOC_LEFT        ��(D)       |�@|��|�b|+0
	{ 0, 1}, // LOC_RIGHT       �E(E)       +--+--+--+
	{ 0, 0}, // LOC_CENTER      ���S        |�@|�d|�a|+1
	//                             +--+--+--+
},
};
// �����ƃ��P�[�V��������A�I�t�Z�b�g�x�N�^�[�擾
Vector2 GetLocationVector2(Direction dir, Location loc)
{
	assert(IsInDirection(dir));
	assert(IsInLocation(loc));
	return locations[dir][loc];
}

// [5-2]��ƂȂ�A�X�L�[�A�[�g��錾����
// +..+==+..+
// .  |  |  .
// +..+..+..+
// .  |��|  .
// +..+..+..+
static const char* all =
"L       /\n"
"#L     /#\n"
"#|L _ /|#\n"
"#|#|#|#|#\n"
"#|#|_|#|#\n"
"#|/   L|#\n"
"#/     L#\n"
"/       L\n";

// [5-3]���O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
// +==+..+..+ (���̕ǂ�`��)
// .  .  .  .
// +..+..+..+
// .  .��.  .
// +..+..+..+
static const char* frontLeftNorth =
"         \n"
"         \n"
"  _      \n"
" |#|     \n"
" |_|     \n"
"         \n"
"         \n"
"         \n";

// [5-4]�E�O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+==+ (���̕ǂ�`��)
// .  .  .  .
// +..+..+..+
// .  .��.  .
// +..+..+..+
static const char* frontRightNorth =
"         \n"
"         \n"
"      _  \n"
"     |#| \n"
"     |_| \n"
"         \n"
"         \n"
"         \n";

// [5-5]�O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+==+..+ (���̕ǂ�`��)
// .  .  .  .
// +..+..+..+
// .  .��.  .
// +..+..+..+
static const char* frontNorth =
"         \n"
"         \n"
"    _    \n"
"   |#|   \n"
"   |_|   \n"
"         \n"
"         \n"
"         \n";

// [5-6]�O�����̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  |  .  . (���̕ǂ�`��)
// +..+..+..+
// .  .��.  .
// +..+..+..+
static const char* frontWest =
"         \n"
"         \n"
" |L      \n"
" |#|     \n"
" |#|     \n"
" |/      \n"
"         \n"
"         \n";

// [5-7]�O���E�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  .  |  . (���̕ǂ�`��)
// +..+..+..+
// .  .��.  .
// +..+..+..+
static const char* frontEast =
"         \n"
"         \n"
"      /| \n"
"     |#| \n"
"     |#| \n"
"      L| \n"
"         \n"
"         \n";

// [5-8]�����O�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  .  .  .
// +==+..+..+ (���̕ǂ�`��)
// .  .��.  .
// +..+..+..+
static const char* leftNorth =
"         \n"
"_        \n"
"#|       \n"
"#|       \n"
"#|       \n"
"_|       \n"
"         \n"
"         \n";

// [5-9]�E���O�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  .  .  .
// +..+..+==+ (���̕ǂ�`��)
// .  .��.  .
// +..+..+..+
static const char* rightNorth =
"         \n"
"        _\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |_\n"
"         \n"
"         \n";

// [5-10]�O�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  .  .  .
// +..+==+..+ (���̕ǂ�`��)
// .  .��.  .
// +..+..+..+
static const char* north =
"         \n"
"  _____  \n"
" |#####| \n"
" |#####| \n"
" |#####| \n"
" |_____| \n"
"         \n"
"         \n";

// [5-11]���̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  .  .  .
// +..+..+..+
// .  |��.  . (���̕ǂ�`��)
// +..+..+..+
static const char* west =
"L        \n"
"#L       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#/       \n"
"/        \n";

// [5-12]�E�̕ǂ̃A�X�L�[�A�[�g��錾����
// +..+..+..+ 
// .  .  .  .
// +..+..+..+
// .  .��|  . (���̕ǂ�`��)
// +..+..+..+
static const char* east =
"        /\n"
"       /#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       L#\n"
"        L\n";

const char* aaTable[LOC_MAX][DIR_MAX] =
{
	// LOC_FRONT_LEFT ���O
	{
		frontLeftNorth,  // DIR_NORTH(�O��)
		nullptr,         // DIR_WEST (����)
		nullptr,         // DIR_SOUTH(���)
		nullptr,         // DIR_EAST (�E��)
	},
	// LOC_FRONT_RIGHT �E�O
	{
		frontRightNorth, // DIR_NORTH(�O��)
		nullptr,         // DIR_WEST (����)
		nullptr,         // DIR_SOUTH(���)
		nullptr,         // DIR_EAST (�E��)
	},
	// LOC_FRONT
	{
		frontNorth,      // DIR_NORTH(�O��)
		frontWest,       // DIR_WEST (����)
		nullptr,         // DIR_SOUTH(���)
		frontEast,       // DIR_EAST (�E��)
	},
	// LOC_LEFT
	{
		leftNorth,       // DIR_NORTH(�O��)
		nullptr,         // DIR_WEST (����)
		nullptr,         // DIR_SOUTH(���)
		nullptr,         // DIR_EAST (�E��)
	},
	// LOC_RIGHT
	{
		rightNorth,      // DIR_NORTH(�O��)
		nullptr,         // DIR_WEST (����)
		nullptr,         // DIR_SOUTH(���)
		nullptr,         // DIR_EAST (�E��)
	},
	// LOC_CENTER
	{
		north,          // DIR_NORTH(�O��)
		west,           // DIR_WEST (����)
		nullptr,        // DIR_SOUTH(���)
		east,           // DIR_EAST (�E��)
	},
};
// �����ƃ��P�[�V��������A�A�X�L�[�A�[�g��������擾
const char* GetLocationAA(Location loc, Direction dir)
{
	assert(IsInDirection(dir));
	assert(IsInLocation(loc));
	return aaTable[loc][dir];
}
// ���P�[�V�����͈̓`�F�b�N
bool IsInLocation(Location loc)
{
	// loc �� 0 �` LOC_MAX-1 �����`�F�b�N���܂�
	// ���������R�[�f�B���O���Ă�������
}