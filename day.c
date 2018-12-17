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
            fprintf(rec,"・%sさん\n",data[i].name);
          }
        }
      }
      printf("\n");
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
