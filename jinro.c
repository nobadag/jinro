#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

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

// �l�f�[�^�̍\����
typedef struct{
  int live; // ����
  char name[26]; // ���O
  char job[20]; // �E�Ɩ�
  int id; // �E�Ɣԍ�
  int doubt; // �Ǖ���c�œ��[����Ă���l��
} people;

typedef struct{
  char writer[14];
  char msg[82];
} write;

int  last(void);
void read(void);
void start(void);
void input(void);
void option();
int set(void);
int check(void);
void record(void);
void open(void);
void day(int*);
void night(int);
void result(void);
void save(void);

int wolf,citizens,prophet,knight,mediumship,traitor;
int first;
int *dice;
double join,live;
people *data;
FILE *rec,*reg,*player,*box;

int main(void)
{
  int die;
  int answer;
  int usable = CAN;

  printf("\n �l�T�Q�[���ɂ悤�����B");
  getchar();
  system("cls");
  answer = last();
  do{
    if(answer == DO_NOT_USE_LAST){
      start();
      input();
      option();
      usable = CAN;
    } else{
      read();
      getchar();
    }
    usable = set();
    if(usable == ERROR){
      getchar();
      system("cls");
      answer = DO_NOT_USE_LAST;
    }
    if(usable == CAN && answer == USE_LAST){
      usable = check();
      if(usable == ERROR){
        answer = DO_NOT_USE_LAST;
      }
    }
  } while(usable == ERROR);
  record();
  open();
  while(wolf < live / 2 || wolf == 0){
    day(&die);
    if(wolf >= live / 2 || wolf == 0) break;
    night(die);
  }
  result();
  save();
  free(data);
  free(dice);
  getchar();
  getchar();
  return 0;
}

int last(void)
{
  int answer;
  char ques[4];

  box = fopen("box.dat","rb");
  if(box == NULL){
    answer = DO_NOT_USE_LAST;
    return answer;
  }
  fclose(box);
  do{
    printf("\n �O��̃f�[�^���g�p���܂����H(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes") != 0 && strcmp(ques,"no") != 0);
  if(strcmp(ques,"yes")== 0){
    answer = USE_LAST;
  } else{
    answer = DO_NOT_USE_LAST;
  }
  return answer;
}

void read(void)
{
  int i;

  reg = fopen("register.csv","r");
  player = fopen("player.csv","r");
  box = fopen("box.dat","rb");

  fscanf(reg,"%lf,%d,%d,%d,%d,%d,%d",&join,&wolf,&prophet,&knight,&mediumship,&traitor,&first);
  live = join;
  citizens = join - wolf - prophet - knight - mediumship - traitor;
  data = malloc(sizeof(people)*join);
  for(i = 0; i < join; i++){
    fscanf(player,"%[^,],",data[i].name);
  }
  dice = malloc(sizeof(int)*join);
  fread(dice,sizeof(int),join,box);
  fclose(reg);
  fclose(player);
  fclose(box);
}

void start(void)
{
  char ques[3];
  join = 4;
  do{
    if(join != 4) printf(" �������l������͂��Ă��������B");
    printf("\n �Q���l������͂��Ă��������B");
    scanf("%2s",ques);
    join = atof(ques);
  } while(join < 4 || join > 20);
  live  = join;
  data = malloc(sizeof(people)*join);
}

void input(void)
{
  int i,int_join;
  time_t relay;

  int_join = (int)join;
  dice = malloc(sizeof(int)*join);
  printf("\n �i�P�Q�����ȓ��j\n");
  for (i = 0; i < join; i++){
    printf(" �Q����%d�̖��O����͂��Ă��������B",(i + 1));
    scanf("%24s",data[i].name);
    relay = time(NULL);
    dice[i] = (int)relay % int_join;
  }
  getchar();
  system("cls");
}

void option(void)
{
  char ques[4];
  int check;

  wolf = 1;
  do{
    if(wolf != 1) printf(" �������l������͂��Ă��������B\n");
    printf("\n %s�̐l����ݒ肵�Ă��������B",WOLF);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    wolf = atoi(ques);
  } while(wolf == 0 || wolf >= join / 2 || check == 0);

  prophet = 1;
  do{
    if(prophet != 1) printf(" �������l������͂��Ă��������B\n");
    printf(" %s�̐l����ݒ肵�Ă��������B",PROPHET);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    prophet = atoi(ques);
  } while(prophet > join - wolf || check == 0);

  knight = 1;
  do{
    if(knight != 1) printf(" �������l������͂��Ă��������B\n");
    printf(" %s�̐l����ݒ肵�Ă��������B",KNIGHT);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    knight = atoi(ques);
  } while(knight > join - wolf - prophet || check == 0);

  mediumship = 1;
  do{
    if(mediumship != 1) printf(" �������l������͂��Ă��������B\n");
    printf(" %s�̐l����ݒ肵�Ă��������B",MEDIUMSHIP);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    mediumship = atoi(ques);
  } while(mediumship > join - wolf - prophet - knight || check == 0);

  traitor = 1;
  do{
    if(traitor != 1) printf(" �������l������͂��Ă��������B\n");
    printf(" %s�̐l����ݒ肵�Ă��������B",TRAITOR);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    traitor = atoi(ques);
  } while(traitor > join - wolf - prophet - knight - mediumship || check == 0);

  citizens = join - wolf - prophet - knight - mediumship - traitor;
  live = join;
  printf(" �����%s�̐l����%d�l�ł��B\n",CITIZENS,citizens);
  getchar();

  do{
    printf("\n �����Ǖ����Ȃ��ɂ��܂����H(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes")!= 0 && strcmp(ques,"no")!= 0);
  getchar();
  system("cls");
  first = strcmp(ques,"yes");
}

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

int check(void)
{
  int i;
  char ques[4];

  printf("\n �Q���l���F%2.0f�l\n",join);
  printf(" %s�̐l���F%d�l\n",WOLF,wolf);
  printf(" %s�̐l���F%d�l\n",PROPHET,prophet);
  printf(" %s�̐l���F%d�l\n",KNIGHT,knight);
  printf(" %s�̐l���F%d�l\n",MEDIUMSHIP,mediumship);
  printf(" %s�̐l���F%d�l\n",TRAITOR,traitor);
  printf(" �����Ǖ��F");
  if(first == SKIP){
    printf("�Ȃ�\n");
  } else{
    printf("����\n");
  }
  printf("\n");
  for(i = 0; i < join; i++){
    printf(" �Q����%d�F%s\n",i + 1,data[i].name);
  }
  do{
    printf("\n ���̃f�[�^�Ő������ł����H(yes or no)");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes")!= 0 && strcmp(ques,"no")!= 0);
  getchar();
  system("cls");
  if(strcmp(ques,"no")== 0){
    return ERROR;
  } else{
    return CAN;
  }
}

void record(void)
{
  int i;

  rec = fopen("log.txt","w");
  reg = fopen("register.csv","w");
  player = fopen("player.csv","w");
  box = fopen("box.dat","wb");

  fprintf(reg,"%f,%d,%d,%d,%d,%d,%d",join,wolf,prophet,knight,mediumship,traitor,first);
  for(i = 0; i < join; i++){
    fprintf(player,"%s,",data[i].name);
  }
  fprintf(rec,"�Q���l���F%2.0f�l\n\n",join);
  for(i = 0; i < join; i++){
    fprintf(rec,"�Q����%d:%s\n",i + 1,data[i].name);
  }
  fprintf(rec,"\n");
  fprintf(rec,"%s�̐l���F%d�l\n",WOLF,wolf);
  fprintf(rec,"%s�̐l���F%d�l\n",PROPHET,prophet);
  fprintf(rec,"%s�̐l���F%d�l\n",KNIGHT,knight);
  fprintf(rec,"%s�̐l���F%d�l\n",MEDIUMSHIP,mediumship);
  fprintf(rec,"%s�̐l���F%d�l\n",TRAITOR,traitor);
  fprintf(rec,"%s�̐l���F%d�l\n",CITIZENS,citizens);
  if(first == SKIP){
    fprintf(rec,"\n�����Ǖ��Ȃ�\n\n");
  } else{
    fprintf(rec,"\n�����Ǖ�����\n\n");
  }
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
            printf("\n");
            fprintf(rec,"�E%s����\n",data[i].name);
          }
        }
      }
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

void night(int die)
{
  static int count;
  static int guard;
  int i,rev,revcount,show,num = 0;
  int who;
  int raid;
  int wcount = 0;
  int *wchoose;
  write *wmsg,diary;
  char ques[3];
  int check;

  wmsg = malloc(sizeof(write)*wolf);
  wchoose = malloc(sizeof(int)*wolf - 1);
  count++;
  rev = ((count % 2) == 0) ? join - 1 : 0;
  revcount = ((count % 2) == 0) ? -1 : join;
  printf("\n %d���ڂ̖�̃^�[���ɂȂ�܂����B\n",count);
  getchar();
  for(i = rev; i != revcount; ){
    if(data[i].live == LIVE){
      printf(" %d�ԁE%s����\n",num + 1,data[i].name);
      num++;
    }
    i = ((count % 2) == 1) ? i + 1 : i - 1;
  }
  printf("\n ���̏��Ԃōs�����Ă��������B\n Enter�L�[�������ƕ��͂������A������x�����Ǝ��̐l�ɐ؂�ւ��܂��B\n");
  fprintf(rec,"\n");
  if(count == 1){
    guard = join;
  }
  for(i = rev ; i != revcount; show++){
    if(data[i].live == LIVE){
      fprintf(rec,"��%s�� �E�ƁF%s\n",data[i].name,data[i].job);
      getchar();
      system("cls");
      printf("\n %s����̖�̍s�����n�߂Ă��������B",data[i].name);
      getchar();
      for(show = 0; show < join; show++){
        if(data[i].id > N_WOLF){
          if(data[show].live == LIVE && show != i){
            printf("\n %d�E%s����",show + 1,data[show].name);
          }
        } else{
          if(data[show].live == LIVE && show != i && data[show].id != N_WOLF){
            printf("\n %d�E%s����",show + 1,data[show].name);
          }
        }
      }
      switch(data[i].id){
        case N_WOLF:
          if(wcount > 0){
            for(show = 0; show < wcount; show++){
              printf("\n\n %s����� %d �Ԃ�I�����܂����B\n\n�E���b�Z�[�W�E\n",wmsg[show].writer,wchoose[show]);
              printf(" %s\n",wmsg[show].msg);
            }
          }
          do{
            printf("\n\n ������P�����܂����H");
            if(wcount == wolf - 1){
              printf("�i���Ȃ������肵�܂��B�j");
            } else{
              printf("�i���Ȃ��͌���ł��܂���j");
            }
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
          } while(who < 0 || who >= join || data[who].live == DIED || data[who].id == N_WOLF || check == 0);
          if(wcount == wolf - 1){
            raid = who;
            fprintf(rec,"�P�������l�i���茠����j�F%s\n",data[who].name);
          } else{
            wchoose[wcount] = who + 1;
            fprintf(rec,"�P�������l�i���茠�Ȃ��j�F%s\n",data[who].name);
          }
          printf("\n ���b�Z�[�W���c���Ă��������B�i�S�O���ȓ��j\n");
          scanf("%40s",wmsg[wcount].msg);
          strcpy(wmsg[wcount].writer,data[i].name);
          getchar();
          wcount++;
          break;

        case N_PROPHET:
          do{
            printf("\n\n �����肢�܂����H");
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
          } while(who < 0 || who >= join || data[who].live == DIED || who == i || check == 0);
          fprintf(rec,"������l�F%s\n",data[who].name);
          if(data[who].id > N_WOLF){
            printf("\n %s�����%s�ł͂���܂���B\n",data[who].name,WOLF);
            fprintf(rec,"���ʁF%s�ł͂Ȃ�\n",WOLF);
          } else{
            printf("\n %s�����%s�ł��B\n",data[who].name,WOLF);
            fprintf(rec,"���ʁF%s�ł���\n",WOLF);
          }
          printf("\n �R�����g�������Ă��������B�i�S�O���ȓ��j\n");
          scanf("%40s",diary.msg);
          getchar();
          break;

        case N_KNIGHT:
          do{
            printf("\n\n ��������܂����H");
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
          } while(who < 0 || who >= join || data[who].live == DIED || who == i || who == guard || check == 0);
          fprintf(rec,"������l�F%s\n",data[who].name);
          guard = who;
          printf("\n �R�����g�������Ă��������B�i�S�O���ȓ��j\n");
          scanf("%40s",diary.msg);
          getchar();
          break;

        case N_MEDIUMSHIP:
          if(count == 1){
            printf("\n\n ���Ȃ��͂Ȃɂ����܂���B\n");
          } else{
            fprintf(rec,"����Ǖ����ꂽ�l�i%s�j�F%s",data[die].name,WOLF);
            if(data[die].id == N_WOLF){
              printf("\n\n �����Ǖ����ꂽ%s����́A%s�ł��B\n",data[die].name,WOLF);
              fprintf(rec, "�ł���\n\n");
            } else{
              printf("\n\n �����Ǖ����ꂽ%s����́A%s�ł͂���܂���B\n",data[die].name,WOLF);
              fprintf(rec, "�ł͂Ȃ�\n\n");
            }
          }
          printf("\n �R�����g�������Ă��������B�i�S�O���ȓ��j\n");
          scanf("%40s",diary.msg);
          getchar();
          break;

        default:
          printf("\n\n ���Ȃ��͂Ȃɂ����܂���B\n");
          printf("\n �R�����g�������Ă��������B�i�S�O���ȓ��j\n");
          scanf("%40s",diary.msg);
          getchar();
          break;
      }
      fprintf(rec," �E�R�����g�E\n");
      switch(data[i].id){
        case N_WOLF:
          fprintf(rec,"%s\n\n",wmsg[wcount - 1].msg);

        default:
          fprintf(rec,"%s\n\n",diary.msg);
          break;
      }
    }
    i = ((count % 2) == 1) ? i + 1 : i - 1;
  }
  if(guard != raid){
    data[raid].live = DIED;
    live--;
  }
  getchar();
  system("cls");
  printf("\n ����...");
  getchar();
  if(guard == raid){
    printf(" ������P������܂���ł����B\n\n");
    fprintf(rec,"������P������Ȃ������B\n");
  } else{
    printf(" %s���񂪏P������܂����B\n\n",data[raid].name);
    fprintf(rec,"�P�����ꂽ�l�F%s����\n",data[raid].name);
  }
  free(wmsg);
  free(wchoose);
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

void save(void)
{
  char ques[4];
  char log_name[24];

  fwrite(dice,sizeof(int),join,box);
  fclose(rec);
  fclose(reg);
  fclose(player);
  fclose(box);

  do{
    printf("\n ���O��ۑ����܂����H(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes") != 0 && strcmp(ques,"no") != 0);
  if(strcmp(ques,"no")== 0){
    remove("log.txt");
  } else{
    printf(" ���O�̖��O����͂��Ă��������B�i�P�Q���ȓ��j");
    scanf("%22s",log_name);
    strcat(log_name,".txt");
    rename("log.txt",log_name);
  }

  do{
    printf("\n ����̃f�[�^��ۑ����܂����H(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes") != 0 && strcmp(ques,"no") != 0);
  if(strcmp(ques,"no")== 0){
    remove("register.csv");
    remove("player.csv");
    remove("box.dat");
  }
}
