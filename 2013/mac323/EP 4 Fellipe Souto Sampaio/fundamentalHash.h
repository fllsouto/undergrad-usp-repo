#ifndef _fundamentalHashLemma_h
#define _fundamentalHashLemma_h
#include "lemmaDefs.h"
typedef char *Key;

static int primetable[] = {251 ,509 ,1021 ,2039 ,4093 ,8191 ,16381 ,32749 ,65521, 131071, 
262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393,67108859, 
134217689, 268435399, 536870909, 1073741789, 2147483647};


int hashFunction(Key, int);
char *arrangeString(char *);
int compareKeys (Key ,Key );
#endif