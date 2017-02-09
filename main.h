#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include "array.h"
#include "blocks.h"

#ifdef INCLUDED_FROM_MAIN
#define EXTERN
#else
#define EXTERN extern
#endif // INCLUDED_FROM_MAIN
/* Временные переменные */
EXTERN unsigned offsetInArray,offsetInFile;

EXTERN unsigned *blockArray,sizeBlockArray,stringSize,stringFileOffset;
EXTERN FILE *arrayFile[4],*stringFile;
int _stdcall compare(unsigned newIndex,unsigned oldIndex);

#endif // MAIN_H_INCLUDED
