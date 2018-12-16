#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "constant.h"

int  last(void);
void read(void);
int check(void);
void record(void);
void save(void);

extern int wolf,citizens,prophet,knight,mediumship,traitor;
extern int first;
extern int *dice;
extern double join,live;
extern people *data;
extern FILE *rec,*reg,*player,*box;

#endif
