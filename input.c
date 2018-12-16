#include "input.h"

int wolf,citizens,prophet,knight,mediumship,traitor;
int first;
int *dice;
double join,live;
people *data;
FILE *rec;

void start(void)
{
  char ques[3];
  join = 4;
  do{
    if(join != 4) printf(" 正しい人数を入力してください。");
    printf("\n 参加人数を入力してください。");
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
  printf("\n （１２文字以内）\n");
  for (i = 0; i < join; i++){
    printf(" 参加者%dの名前を入力してください。",(i + 1));
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
    if(wolf != 1) printf(" 正しい人数を入力してください。\n");
    printf("\n %sの人数を設定してください。",WOLF);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    wolf = atoi(ques);
  } while(wolf == 0 || wolf >= join / 2 || check == 0);

  prophet = 1;
  do{
    if(prophet != 1) printf(" 正しい人数を入力してください。\n");
    printf(" %sの人数を設定してください。",PROPHET);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    prophet = atoi(ques);
  } while(prophet > join - wolf || check == 0);

  knight = 1;
  do{
    if(knight != 1) printf(" 正しい人数を入力してください。\n");
    printf(" %sの人数を設定してください。",KNIGHT);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    knight = atoi(ques);
  } while(knight > join - wolf - prophet || check == 0);

  mediumship = 1;
  do{
    if(mediumship != 1) printf(" 正しい人数を入力してください。\n");
    printf(" %sの人数を設定してください。",MEDIUMSHIP);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    mediumship = atoi(ques);
  } while(mediumship > join - wolf - prophet - knight || check == 0);

  traitor = 1;
  do{
    if(traitor != 1) printf(" 正しい人数を入力してください。\n");
    printf(" %sの人数を設定してください。",TRAITOR);
    scanf("%2s",ques);
    check = isdigit(ques[0]);
    traitor = atoi(ques);
  } while(traitor > join - wolf - prophet - knight - mediumship || check == 0);

  citizens = join - wolf - prophet - knight - mediumship - traitor;
  live = join;
  printf(" よって%sの人数は%d人です。\n",CITIZENS,citizens);
  getchar();

  do{
    printf("\n 初日追放をなしにしますか？(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes")!= 0 && strcmp(ques,"no")!= 0);
  getchar();
  system("cls");
  first = strcmp(ques,"yes");
}
