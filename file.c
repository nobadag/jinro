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

  box = fopen(".\\Datas\\box.dat","rb");
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

  reg = fopen(".\\Datas\\register.csv","r");
  player = fopen(".\\Datas\\player.csv","r");
  box = fopen(".\\Datas\\box.dat","rb");

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

  rec = fopen(".\\Logs\\log.txt","w");
  reg = fopen(".\\Datas\\register.csv","w");
  player = fopen(".\\Datas\\player.csv","w");
  box = fopen(".\\Datas\\box.dat","wb");

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

void save(void)
{
  char ques[4];
  char log_name[25];
  char log_file[35];

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
    remove(".\\Logs\\log.txt");
  } else{
    printf(" ���O�̖��O����͂��Ă��������B�i�P�Q���ȓ��j");
    scanf("%22s",log_name);
    sprintf(log_file,"%s%s%s",".\\Logs\\",log_name,".txt");
    rename(".\\Logs\\log.txt",log_file);
  }

  do{
    printf("\n ����̃f�[�^��ۑ����܂����H(yes or no) ");
    scanf("%3s",ques);
  } while(strcmp(ques,"yes") != 0 && strcmp(ques,"no") != 0);
  if(strcmp(ques,"no")== 0){
    remove(".\\Datas\\register.csv");
    remove(".\\Datas\\player.csv");
    remove(".\\Datas\\box.dat");
  }
}
