/*
    This file is part of archiver project
    Copyright © 2017  Feshchukov Aristarh <fe.arik@yandex.ru>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "main.h"

#ifdef DEBUG
#define CHANGE_TRACING(oldOffset) printf("Changing from %u to %u\n",index,oldOffset)
#else
#define CHANGE_TRACING(oldOffset)
#endif // DEBUG

#define CHANGE(oldInd,oldOffset) offsetInArray=(oldOffset)/(1<<30);\
    offsetInFile=(oldOffset)%(1<<30)*sizeof(int);\
    CHANGE_TRACING(oldOffset);\
    fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);\
    fwrite(&newIndex,sizeof(int),1,arrayFile[offsetInArray]);\
    offsetInArray=(index)/(1<<30);offsetInFile=(index)%(1<<30)*sizeof(int);\
    fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);\
    fwrite(&oldInd,sizeof(int),1,arrayFile[offsetInArray]);\
    index=oldOffset;

static void _stdcall createBinHeap()
{
    unsigned i,newIndex,oldIndex,index,indexNext;
    fseek(arrayFile[0],0,SEEK_SET);
    newIndex=0;
    fwrite(&newIndex,sizeof(int),1,arrayFile[0]);
    for(i=1; i<stringSize; i++)
    {
        newIndex=i;
        index=i;
        fseek(arrayFile[index/(1<<30)],index%(1<<30)*sizeof(int),SEEK_SET);
        fwrite(&newIndex,sizeof(int),1,arrayFile[index/(1<<30)]);
        while(index!=0)
        {
#ifdef DEBUG
            printf("Tracing: ");
            int b;
            fseek(arrayFile[0],0,SEEK_SET);
            for(unsigned a=0; a<=i; a++)
            {
                fread(&b,sizeof(int),1,arrayFile[0]);
                printf("%u ",b);
            }
            printf("\n");
#endif // DEBUG
            indexNext=(index-1)/2;
            offsetInArray=indexNext/(1<<30);
            offsetInFile=indexNext%(1<<30)*sizeof(int);
            fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);
            fread(&oldIndex,sizeof(int),1,arrayFile[offsetInArray]);
            if(compare(newIndex,oldIndex)>0)
            {
                CHANGE(oldIndex,indexNext);
            }
            else
            {
                break;
            }
        }
#ifdef DEBUG
        printf("Result: ");
        int b;
        fseek(arrayFile[0],0,SEEK_SET);
        for(unsigned a=0; a<=i; a++)
        {
            fread(&b,sizeof(int),1,arrayFile[0]);
            printf("%u ",b);
        }
        printf("\n");
#endif // DEBUG
    }
}

void _stdcall sortArray()
{
    unsigned i,newIndex,buff1,buff2;
    createBinHeap(arrayFile,stringSize);
#ifdef DEBUG
    printf("Starting sorting\n");
#endif // DEBUG
    for(i=stringSize-1; i>0; i--)
    {
        offsetInArray=i/(1<<30);
        offsetInFile=i%(1<<30)*sizeof(int);
        fseek(arrayFile[0],0,SEEK_SET);
        fread(&buff1,sizeof(int),1,arrayFile[0]);
        fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);
        fread(&newIndex,sizeof(int),1,arrayFile[offsetInArray]);
        fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);
        fwrite(&buff1,sizeof(int),1,arrayFile[offsetInArray]);
        fseek(arrayFile[0],0,SEEK_SET);
        fwrite(&newIndex,sizeof(int),1,arrayFile[0]);
        unsigned index=0;
        for(;;)
        {
            if(2*index+1<=i)
            {
                offsetInArray=(2*index+1)/(1<<30);
                offsetInFile=(2*index+1)%(1<<30)*sizeof(int);
                fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);
                fread(&buff1,sizeof(int),1,arrayFile[offsetInArray]);
                if(2*index+2<=i)
                {
                    offsetInArray=(2*index+2)/(1<<30);
                    offsetInFile=(2*index+2)%(1<<30)*sizeof(int);
                    fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);
                    fread(&buff2,sizeof(int),1,arrayFile[offsetInArray]);
                }
                else
                {
                    buff2=-1;
                }
            }
            else
            {
                buff1=-1;
                buff2=-1;
            }
            if(compare(newIndex,buff1)>=0)
            {
                if(compare(newIndex,buff2)>=0)
                {
                    break;
                }
                else
                {
                    CHANGE(buff2,2*index+2);
                }
            }
            else
            {
                if(compare(newIndex,buff2)>=0)
                {
                    CHANGE(buff1,2*index+1);
                }
                else
                {
                    if(compare(buff1,buff2)>0)
                    {
                        CHANGE(buff1,2*index+1);
                    }
                    else
                    {
                        CHANGE(buff2,2*index+2);
                    }
                }
            }
        }
    }
}


