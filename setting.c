#include "setting.h"

int wolf,citizens,prophet,knight,mediumship,traitor;
int first;
int *dice;
double join,live;
people *data;
FILE *rec;

int set(void)
{
  int i,relay,med;
  int *values;

  if(join == 0){
    printf("\n �t�@�C������f�[�^��ǂݍ��߂܂���ł����B\n ������x���͂��Ȃ����Ă��������B");
    return ERROR;
  }
  values = malloc(sizeof(int)*join);
  for(i = 0; i < join; i++){
    data[i].live = 1;
    data[i].doubt = 0;
  }
  for(i = 0; i < join; i++){
    values[i] = i;
  }
  for(i = 0; i < join; i++){
    med = dice[i];
    relay = values[i];
    values[i] = values[med];
    values[med] = relay;
  }
  for(i = 0; i < join; i++){
    med = values[i];
    if(med < wolf){
      data[i].id = N_WOLF;
      strcpy(data[i].job,WOLF);
    } else if(med >= wolf && med < wolf + prophet){
      data[i].id = N_PROPHET;
      strcpy(data[i].job,PROPHET);
    } else if(med >= wolf + prophet && med < wolf + prophet + knight){
      data[i].id = N_KNIGHT;
      strcpy(data[i].job,KNIGHT);
    } else if(med >= wolf + prophet + knight && med < wolf + prophet + knight + mediumship){
      data[i].id = N_MEDIUMSHIP;
      strcpy(data[i].job,MEDIUMSHIP);
    } else if(med >= wolf + prophet + knight + mediumship && med < wolf + prophet + knight + mediumship + traitor){
      data[i].id = N_TRAITOR;
      strcpy(data[i].job,TRAITOR);
    } else{
      data[i].id = N_CITIZENS;
      strcpy(data[i].job,CITIZENS);
    }
  }
  return 0;
}

void open(void)
{
  int i,show;
  int int_join;
  time_t relay;

  int_join = (int)join;
  printf("\n �������E�������܂��B\n\n");
  for(i = 0; i < join; i++){
    printf(" %d�ԁ@%s����\n",i + 1,data[i].name);
  }
  printf("\n ���̏��ԂŌ��Ă��������B\n Enter�L�[�������ƕ��͂������A������x�����Ǝ��̐l�ɐ؂�ւ��܂��B");
  getchar();
  system("cls");
  for(i = 0; i < join; i++){
    getchar();
    printf("\n %s����̖�E��",data[i].name);
    getchar();
    printf(" %s�ł��B",data[i].job);
    if(data[i].id == 0){
      if(wolf > 1){
        printf(" ���Ȃ��̒��Ԃ� ");
        for(show = 0; show < join; show++){
          if(data[show].id == 0 && show != i){
            printf(" %s ���� ",data[show].name);
          }
        }
        printf("�ł��B");
      }
    }
    fprintf(rec,"%s�̖�E�F%s\n",data[i].name,data[i].job);
    getchar();
    system("cls");
    relay = time(NULL);
    dice[i] = relay % int_join;
  }
}

void result()
{
  int i;
  int winner;

  winner = (wolf != 0) ? 0 : 1;

  printf("\n �����ŃQ�[���͏I���ł��B\n");
  fprintf(rec,"\n�Q�[���I��\n\n");
  printf("\n ���҂�... ");
  fprintf(rec,"���ҁF");
  getchar();
  if(winner == 0){
    printf(" %s�`�[���ł��I\n ",WOLF);
    fprintf(rec,"%s�`�[��\n",WOLF);
    getchar();
    for(i = 0; i < join; i++){
      if(data[i].id == 0 || data[i].id == 5){
        printf(" %s����,",data[i].name);
        fprintf(rec,"%s����A",data[i].name);
      }
    }
    printf("���߂łƂ��������܂��I\n");

  } else if(winner == 1){
    printf(" %s�`�[���ł��I\n ",CITIZENS);
    fprintf(rec,"%s�`�[��\n",CITIZENS);
    getchar();
    for(i = 0; i < join; i++){
      if(data[i].id > 0 && data[i].id != 5){
        printf(" %s����,",data[i].name);
        fprintf(rec,"%s����A",data[i].name);
      }
    }
    printf("���߂łƂ��������܂��I\n");
  }
  getchar();
  system("cls");
}
