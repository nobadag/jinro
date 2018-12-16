#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

// 個人データの構造体
typedef struct{
  int live; // 生死
  char name[26]; // 名前
  char job[20]; // 職業名
  int id; // 職業番号
  int doubt; // 追放会議で投票されている人数
} people;

// メッセージ用の構造体
typedef struct{
  char writer[14]; // 書いた人
  char msg[82]; // 内容
} write;

#endif
