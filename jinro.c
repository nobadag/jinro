#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

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

// 個人データの構造体
typedef struct{
  int live; // 生死
  char name[26]; // 名前
  char job[20]; // 職業名
  int id; // 職業番号
  int doubt; // 追放会議で投票されている人数
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

  printf("\n 人狼ゲームにようこそ。");
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
      printf("\n %d日目の昼のターンになりました。\n 初日追放はありません。\n 会議を始めてください。\n 会議が終了したらEnterキーを押してください。\n",count);
      getchar();
      system("cls");
      return;
    }
  }
  printf("\n %d日目の昼のターンになりました。\n 追放会議を始めてください。\n 会議が終了したらEnterキーを押してください。\n",count);
  fprintf(rec,"\n %d日目\n\n",count);
  getchar();
  for(i = 0; i < join; i++){
    if(data[i].live == 1){
      printf(" %d・%sさん\n",i + 1,data[i].name);
    }
  }
  printf("\n");
  do{
    who = 0;
      for(i = 0; i < join; i++){
        acp = 1;
        if(num == 3){
          do{
            printf("\n 負けた人：");
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
              printf(" 正しい番号を入力してください。");
            }
          } while(who < 0 || who > join - 1 || data[who].live == 0 || acp != 0  || check == 0);
          data[who].doubt++;
          fprintf(rec,"じゃんけんで負けた人：%sさん\n",data[who].name);
          break;
        }
        if(data[i].live == 1){
          if(num == 0){
            do{
              printf(" %sさんの人狼だと思う人の番号を選択してください。",data[i].name);
              scanf("%2s",ques);
              check = isdigit(ques[0]);
              who = atoi(ques);
              who--;
              if(who < 0 || who > join - 1 || who == i || data[who].live == 0 || check == 0){
                printf(" 正しい番号を入力してください。\n");
              }
            } while(who < 0 || who > join - 1 || who == i || data[who].live == 0 || check == 0);
            fprintf(rec,"%sさんの人狼だと思う人：%sさん\n",data[i].name,data[who].name);
            data[who].doubt++;
          } else{
            do{
              printf(" %sさんの人狼だと思う人の番号を選択してください。",data[i].name);
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
                printf(" 正しい番号を入力してください。\n");
              }
            } while(who < 0 || who > join - 1 || who == i || data[who].live == 0 || acp != 0 || check == 0);
            fprintf(rec,"%sさんの人狼だと思う人：%sさん\n",data[i].name,data[who].name);
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
        printf("\n 決戦投票が3回目となりました。この中でじゃんけんをして、負けた人の番号を入力してください。\n\n");
        fprintf(rec,"\nじゃんけん\n 候補\n");
      } else{
        printf("\n 決戦投票となりました。この中から選んでください。\n\n");
        fprintf(rec,"\n決戦投票\n 候補\n");
      }
      for(i = 0; i < join; i++){
        for(ins = 0; ins <= elm; ins++){
          if(i == candi[ins]){
            printf(" %d・%sさん\n",i + 1,data[i].name);
            printf("\n");
            fprintf(rec,"・%sさん\n",data[i].name);
          }
        }
      }
    } else{
      printf("\n %sさんが追放されました。\n",data[big_num].name);
      fprintf(rec,"\n %sさんが追放\n\n",data[big_num].name);
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
  printf("\n %d日目の夜のターンになりました。\n",count);
  getchar();
  for(i = rev; i != revcount; ){
    if(data[i].live == LIVE){
      printf(" %d番・%sさん\n",num + 1,data[i].name);
      num++;
    }
    i = ((count % 2) == 1) ? i + 1 : i - 1;
  }
  printf("\n この順番で行動してください。\n Enterキーを押すと文章が消え、もう一度押すと次の人に切り替わります。\n");
  fprintf(rec,"\n");
  if(count == 1){
    guard = join;
  }
  for(i = rev ; i != revcount; show++){
    if(data[i].live == LIVE){
      fprintf(rec,"＜%s＞ 職業：%s\n",data[i].name,data[i].job);
      getchar();
      system("cls");
      printf("\n %sさんの夜の行動を始めてください。",data[i].name);
      getchar();
      for(show = 0; show < join; show++){
        if(data[i].id > N_WOLF){
          if(data[show].live == LIVE && show != i){
            printf("\n %d・%sさん",show + 1,data[show].name);
          }
        } else{
          if(data[show].live == LIVE && show != i && data[show].id != N_WOLF){
            printf("\n %d・%sさん",show + 1,data[show].name);
          }
        }
      }
      switch(data[i].id){
        case N_WOLF:
          if(wcount > 0){
            for(show = 0; show < wcount; show++){
              printf("\n\n %sさんは %d 番を選択しました。\n\n・メッセージ・\n",wmsg[show].writer,wchoose[show]);
              printf(" %s\n",wmsg[show].msg);
            }
          }
          do{
            printf("\n\n だれを襲撃しますか？");
            if(wcount == wolf - 1){
              printf("（あなたが決定します。）");
            } else{
              printf("（あなたは決定できません）");
            }
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
          } while(who < 0 || who >= join || data[who].live == DIED || data[who].id == N_WOLF || check == 0);
          if(wcount == wolf - 1){
            raid = who;
            fprintf(rec,"襲撃した人（決定権あり）：%s\n",data[who].name);
          } else{
            wchoose[wcount] = who + 1;
            fprintf(rec,"襲撃した人（決定権なし）：%s\n",data[who].name);
          }
          printf("\n メッセージを残してください。（４０字以内）\n");
          scanf("%40s",wmsg[wcount].msg);
          strcpy(wmsg[wcount].writer,data[i].name);
          getchar();
          wcount++;
          break;

        case N_PROPHET:
          do{
            printf("\n\n だれを占いますか？");
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
          } while(who < 0 || who >= join || data[who].live == DIED || who == i || check == 0);
          fprintf(rec,"占った人：%s\n",data[who].name);
          if(data[who].id > N_WOLF){
            printf("\n %sさんは%sではありません。\n",data[who].name,WOLF);
            fprintf(rec,"結果：%sではない\n",WOLF);
          } else{
            printf("\n %sさんは%sです。\n",data[who].name,WOLF);
            fprintf(rec,"結果：%sである\n",WOLF);
          }
          printf("\n コメントを書いてください。（４０字以内）\n");
          scanf("%40s",diary.msg);
          getchar();
          break;

        case N_KNIGHT:
          do{
            printf("\n\n だれを守りますか？");
            scanf("%2s",ques);
            check = isdigit(ques[0]);
            who = atoi(ques);
            who--;
          } while(who < 0 || who >= join || data[who].live == DIED || who == i || who == guard || check == 0);
          fprintf(rec,"守った人：%s\n",data[who].name);
          guard = who;
          printf("\n コメントを書いてください。（４０字以内）\n");
          scanf("%40s",diary.msg);
          getchar();
          break;

        case N_MEDIUMSHIP:
          if(count == 1){
            printf("\n\n あなたはなにもしません。\n");
          } else{
            fprintf(rec,"昨日追放された人（%s）：%s",data[die].name,WOLF);
            if(data[die].id == N_WOLF){
              printf("\n\n 今日追放された%sさんは、%sです。\n",data[die].name,WOLF);
              fprintf(rec, "である\n\n");
            } else{
              printf("\n\n 今日追放された%sさんは、%sではありません。\n",data[die].name,WOLF);
              fprintf(rec, "ではない\n\n");
            }
          }
          printf("\n コメントを書いてください。（４０字以内）\n");
          scanf("%40s",diary.msg);
          getchar();
          break;

        default:
          printf("\n\n あなたはなにもしません。\n");
          printf("\n コメントを書いてください。（４０字以内）\n");
          scanf("%40s",diary.msg);
          getchar();
          break;
      }
      fprintf(rec," ・コメント・\n");
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
  printf("\n 昨夜は...");
  getchar();
  if(guard == raid){
    printf(" だれも襲撃されませんでした。\n\n");
    fprintf(rec,"だれも襲撃されなかった。\n");
  } else{
    printf(" %sさんが襲撃されました。\n\n",data[raid].name);
    fprintf(rec,"襲撃された人：%sさん\n",data[raid].name);
  }
  free(wmsg);
  free(wchoose);
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
