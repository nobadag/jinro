#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "structure.h"
#include "constant.h"

void start(void);
void input(void);
void option(void);

extern int wolf,citizens,prophet,knight,mediumship,traitor;
extern int first;
extern int *dice;
extern double join,live;
extern people *data;
extern FILE *rec;

#endif
