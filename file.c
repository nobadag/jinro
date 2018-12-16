#include "file.h"

int wolf,citizens,prophet,knight,mediumship,traitor;
int first;
int *dice;
double join,live;
people *data;
FILE *rec,*reg,*player,*box;

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
    printf("\n 前回のデータを使用しますか？(yes or no) ");
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

int check(void)
{
  int i;
  char ques[4];

  printf("\n 参加人数：%2.0f人\n",join);
  printf(" %sの人数：%d人\n",WOLF,wolf);
  printf(" %sの人数：%d人\n",PROPHET,prophet);
  printf(" %sの人数：%d人\n",KNIGHT,knight);
  printf(" %sの人数：%d人\n",MEDIUMSHIP,mediumship);
  printf(" %sの人数：%d人\n",TRAITOR,traitor);
  printf(" 初日追放：");
  if(first == SKIP){
    printf("なし\n");
  } else{
    printf("あり\n");
  }
  printf("\n");
  for(i = 0; i < join; i++){
    printf(" 参加者%d：%s\n",i + 1,data[i].name);
  }
  do{
    printf("\n このデータで正しいですか？(yes or no)");
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
  fprintf(rec,"参加人数：%2.0f人\n\n",join);
  for(i = 0; i < join; i++){
    fprintf(rec,"参加者%d:%s\n",i + 1,data[i].name);
  }
  fprintf(rec,"\n");
  fprintf(rec,"%sの人数：%d人\n",WOLF,wolf);
  fprintf(rec,"%sの人数：%d人\n",PROPHET,prophet);
  fprintf(rec,"%sの人数：%d人\n",KNIGHT,knight);
  fprintf(rec,"%sの人数：%d人\n",MEDIUMSHIP,mediumship);
  fprintf(rec,"%sの人数：%d人\n",TRAITOR,traitor);
  fprintf(rec,"%sの人数：%d人\n",CITIZENS,citizens);
  if(first == SKIP){
    fprintf(rec,"\n初日追放なし\n\n");
  } else{
    fprintf(rec,"\n初日追放あり\n\n");
  }
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
    printf("\n ログを保存しますか？(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes") != 0 && strcmp(ques,"no") != 0);
  if(strcmp(ques,"no")== 0){
    remove("log.txt");
  } else{
    printf(" ログの名前を入力してください。（１２字以内）");
    scanf("%22s",log_name);
    strcat(log_name,".txt");
    rename("log.txt",log_name);
  }

  do{
    printf("\n 今回のデータを保存しますか？(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes") != 0 && strcmp(ques,"no") != 0);
  if(strcmp(ques,"no")== 0){
    remove("register.csv");
    remove("player.csv");
    remove("box.dat");
  }
}
