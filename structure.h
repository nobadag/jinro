#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

// �l�f�[�^�̍\����
typedef struct{
  int live; // ����
  char name[26]; // ���O
  char job[20]; // �E�Ɩ�
  int id; // �E�Ɣԍ�
  int doubt; // �Ǖ���c�œ��[����Ă���l��
} people;

// ���b�Z�[�W�p�̍\����
typedef struct{
  char writer[14]; // �������l
  char msg[82]; // ���e
} write;

#endif
