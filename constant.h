#ifndef _CONSTANT_H_
#define _CONSTANT_H_

// 10�����ȓ��Ȃ�OK
#define WOLF "�l�T"
#define CITIZENS "�s��"
#define PROPHET "�肢�t"
#define KNIGHT "�{�f�B�[�K�[�h"
#define MEDIUMSHIP "��}�t"
#define TRAITOR "���؂��"

// �E�Ƃ̔ԍ�
enum {
  N_WOLF,
  N_CITIZENS,
  N_PROPHET,
  N_KNIGHT,
  N_MEDIUMSHIP,
  N_TRAITOR,
};

// �����̔ԍ�
#define DIED 0
#define LIVE 1

// �����Ǖ����΂��ԍ�
#define SKIP 0

// �O��̃f�[�^���g�����ԍ�
#define USE_LAST 1
#define DO_NOT_USE_LAST 0

// �O��̃f�[�^���g���邩�̔ԍ�
#define ERROR 1
#define CAN 0

#endif
