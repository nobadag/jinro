#ifndef _CONSTANT_H_
#define _CONSTANT_H_

// 10文字以内ならOK
#define WOLF "人狼"
#define CITIZENS "市民"
#define PROPHET "占い師"
#define KNIGHT "ボディーガード"
#define MEDIUMSHIP "霊媒師"
#define TRAITOR "裏切り者"

// 職業の番号
enum {
  N_WOLF,
  N_CITIZENS,
  N_PROPHET,
  N_KNIGHT,
  N_MEDIUMSHIP,
  N_TRAITOR,
};

// 生死の番号
#define DIED 0
#define LIVE 1

// 初日追放を飛ばす番号
#define SKIP 0

// 前回のデータを使うか番号
#define USE_LAST 1
#define DO_NOT_USE_LAST 0

// 前回のデータを使えるかの番号
#define ERROR 1
#define CAN 0

#endif
