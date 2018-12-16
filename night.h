#ifndef _NIGHT_H_
#define _NIGHT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "structure.h"
#include "constant.h"

void night(int);

extern int wolf,citizens,prophet,knight,mediumship,traitor;
extern int first;
extern double join,live;
extern people *data;
extern FILE *rec;

#endif
