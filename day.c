#include "day.h"

int wolf;
int first;
double join,live;
people *data;
FILE *rec;

void day(int *die)
{
  static int count;
  int i,who,ins,acp,num = 0;
  int big = 0,big_num,elm = 0,*candi;
  char ques[3];
  int check;

  count++;
  candi = malloc(sizeof(int));
  if(count == 1){
    if(first == SKIP){
      printf("\n %d���ڂ̒��̃^�[���ɂȂ�܂����B\n �����Ǖ��͂���܂���B\n ��c���n�߂Ă��������B\n ��c���I��������Enter�L�[�������Ă��������B\n",count);
      getchar();
      system("cls");
      return;
    }
  }
  printf("\n %d���ڂ̒��̃^�[���ɂȂ�܂����B\n �Ǖ���c���n�߂Ă��������B\n ��c���I��������Enter�L�[�������Ă��������B\n",count);
  fprintf(rec,"\n %d����\n\n",count);
  getchar();
  for(i = 0; i < join; i++){
    if(data[i].live == 1){
      printf(" %d�E%s����\n",i + 1,data[i].name);
    }
  }
  printf("\n");
  do{
    who = 0;
      for(i = 0; i < join; i++){
        acp = 1;
        if(num == 3){
          do{
            printf("\n �������l�F");
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
            for(ins = 0; ins <= elm; ins++){
              if(who == candi[ins]) {
                acp = 0;
                break;
              }
            }
            if(who < 0 || who > join - 1 || data[who].live == 0 || acp != 0  || check == 0){
              printf(" �������ԍ�����͂��Ă��������B");
            }
          } while(who < 0 || who > join - 1 || data[who].live == 0 || acp != 0  || check == 0);
          data[who].doubt++;
          fprintf(rec,"����񂯂�ŕ������l�F%s����\n",data[who].name);
          break;
        }
        if(data[i].live == 1){
          if(num == 0){
            do{
              printf(" %s����̐l�T���Ǝv���l�̔ԍ���I�����Ă��������B",data[i].name);
              scanf("%2s",ques);
              check = isdigit(ques[0]);
              who = atoi(ques);
              who--;
              if(who < 0 || who > join - 1 || who == i || data[who].live == 0 || check == 0){
                printf(" �������ԍ�����͂��Ă��������B\n");
              }
            } while(who < 0 || who > join - 1 || who == i || data[who].live == 0 || check == 0);
            fprintf(rec,"%s����̐l�T���Ǝv���l�F%s����\n",data[i].name,data[who].name);
            data[who].doubt++;
          } else{
            do{
              printf(" %s����̐l�T���Ǝv���l�̔ԍ���I�����Ă��������B",data[i].name);
              scanf("%2s",ques);
              check = isdigit(ques[0]);
              who = atoi(ques);
              who--;
              for(ins = 0; ins <= elm; ins++){
                if(who == candi[ins]) {
                  acp = 0;
                  break;
                }
              }
              if(who < 0 || who > join - 1 || who == i || data[who].live == 0 || acp != 0 || check == 0){
                printf(" �������ԍ�����͂��Ă��������B\n");
              }
            } while(who < 0 || who > join - 1 || who == i || data[who].live == 0 || acp != 0 || check == 0);
            fprintf(rec,"%s����̐l�T���Ǝv���l�F%s����\n",data[i].name,data[who].name);
            data[who].doubt++;
          }
        }
      }
    big = 0;
    for(i = 0; i < join; i++){
      if(data[i].doubt > big){
        big = data[i].doubt;
        big_num = i;
      }
    }
    elm = 0;
    for(i = 0; i < join; i++){
      if(data[i].doubt == big){
        candi = realloc(candi,sizeof(int)*(elm + 1));
        candi[elm] = i;
        elm++;
      }
    }
    num++;
    getchar();
    if(elm > 1){
      if(num == 3){
        printf("\n ���퓊�[��3��ڂƂȂ�܂����B���̒��ł���񂯂�����āA�������l�̔ԍ�����͂��Ă��������B\n\n");
        fprintf(rec,"\n����񂯂�\n ���\n");
      } else{
        printf("\n ���퓊�[�ƂȂ�܂����B���̒�����I��ł��������B\n\n");
        fprintf(rec,"\n���퓊�[\n ���\n");
      }
      for(i = 0; i < join; i++){
        for(ins = 0; ins <= elm; ins++){
          if(i == candi[ins]){
            printf(" %d�E%s����\n",i + 1,data[i].name);
            fprintf(rec,"�E%s����\n",data[i].name);
          }
        }
      }
      printf("\n");
    } else{
      printf("\n %s���񂪒Ǖ�����܂����B\n",data[big_num].name);
      fprintf(rec,"\n %s���񂪒Ǖ�\n\n",data[big_num].name);
      *die = big_num;
      num = 0;
    }
    for(i = 0; i < join; i++){
      data[i].doubt = 0;
    }
  } while(num != 0);
  data[*die].live = 0;
  if(data[*die].id == 0) {
    wolf--;
  }
  live--;
  getchar();
  system("cls");
  free(candi);
}
