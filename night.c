#include "night.h"

int wolf,citizens,prophet,knight,mediumship,traitor;
int first;
double join,live;
people *data;
FILE *rec;

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
