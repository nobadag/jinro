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
