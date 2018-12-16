#ifndef _SETTING_H_
#define _SETTING_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "constant.h"

int set(void);
void open(void);
void result(void);

extern int wolf,citizens,prophet,knight,mediumship,traitor;
extern int first;
extern int *dice;
extern double join,live;
extern people *data;
extern FILE *rec;

#endif
