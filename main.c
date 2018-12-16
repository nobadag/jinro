#include <stdio.h>
#include <stdlib.h>

#include "day.h"
#include "night.h"
#include "file.h"
#include "input.h"
#include "setting.h"

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

  printf("\n êlòTÉQÅ[ÉÄÇ…ÇÊÇ§Ç±ÇªÅB");
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
