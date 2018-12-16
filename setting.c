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
    printf("\n ファイルからデータを読み込めませんでした。\n もう一度入力しなおしてください。");
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
  printf("\n 今から役職を告げます。\n\n");
  for(i = 0; i < join; i++){
    printf(" %d番　%sさん\n",i + 1,data[i].name);
  }
  printf("\n この順番で見てください。\n Enterキーを押すと文章が消え、もう一度押すと次の人に切り替わります。");
  getchar();
  system("cls");
  for(i = 0; i < join; i++){
    getchar();
    printf("\n %sさんの役職は",data[i].name);
    getchar();
    printf(" %sです。",data[i].job);
    if(data[i].id == 0){
      if(wolf > 1){
        printf(" あなたの仲間は ");
        for(show = 0; show < join; show++){
          if(data[show].id == 0 && show != i){
            printf(" %s さん ",data[show].name);
          }
        }
        printf("です。");
      }
    }
    fprintf(rec,"%sの役職：%s\n",data[i].name,data[i].job);
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

  printf("\n ここでゲームは終了です。\n");
  fprintf(rec,"\nゲーム終了\n\n");
  printf("\n 勝者は... ");
  fprintf(rec,"勝者：");
  getchar();
  if(winner == 0){
    printf(" %sチームです！\n ",WOLF);
    fprintf(rec,"%sチーム\n",WOLF);
    getchar();
    for(i = 0; i < join; i++){
      if(data[i].id == 0 || data[i].id == 5){
        printf(" %sさん,",data[i].name);
        fprintf(rec,"%sさん、",data[i].name);
      }
    }
    printf("おめでとうございます！\n");

  } else if(winner == 1){
    printf(" %sチームです！\n ",CITIZENS);
    fprintf(rec,"%sチーム\n",CITIZENS);
    getchar();
    for(i = 0; i < join; i++){
      if(data[i].id > 0 && data[i].id != 5){
        printf(" %sさん,",data[i].name);
        fprintf(rec,"%sさん、",data[i].name);
      }
    }
    printf("おめでとうございます！\n");
  }
  getchar();
  system("cls");
}
