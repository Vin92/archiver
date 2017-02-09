/*
    This file is part of archiver project
    Copyright й 2017  Feshchukov Aristarh <fe.arik@yandex.ru>

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
#define min(a,b) (a>b)?b:a
#define max(a,b) (a<b)?b:a
#define INCLUDED_FROM_MAIN

#include "main.h"

#define MIN_COMPARE 4


/*  ╘юЁьрЄ ьрёёштр сыюъют:
    sizeBlockArray - ъюышўхёЄтю сыюъют т ьрёёштх;
    blockArray[i] - ьръёшьры№э√щ тючьюцэ√щ шэфхъё, яЁшэрфыхцр∙шщ фрээюьє сыюъє.
*/


int _stdcall
#ifdef DEBUG
_compare
#else
compare
#endif // DEBUG
(unsigned newIndex,unsigned oldIndex)
{
    /*
    1: new сюы№°х old
    -1: new ьхэ№°х old
    n: ёютярфхэшх т n ёшьтюырї, new сюы№°х old
    -n: new ьхэ№°х old
    */
    unsigned newLen=getLen(newIndex),oldLen=getLen(oldIndex);
    unsigned i,rect=min(newLen,oldLen);
    if(rect==0)
    {
        return 0;
    }
    /* ╟фхё№ ьюцхЄ с√Є№ сру, Єръ ъръ тючтЁр∙рхЄё  эюы№ */
    char first,second;
    int counter=0;
    for(i=0; i<rect; i++)
    {
        fseek(stringFile,i+newIndex+stringFileOffset,SEEK_SET);
        first=fgetc(stringFile);
        fseek(stringFile,i+oldIndex+stringFileOffset,SEEK_SET);
        second=fgetc(stringFile);
        if(first>second)
        {
            return(max(counter,1));
        }
        else
        {
            if(first<second)
            {
                return(min(-counter,-1));
            }
            else
            {
                counter++;
            }
        }
    }
    if(newLen>oldLen)
    {
        return(max(counter,1));
    }
    else
    {
        return(min(-counter,-1));
    }
}

#ifdef DEBUG
int _stdcall compare(unsigned newIndex,unsigned oldIndex)
{
    int result=_compare(newIndex,oldIndex);
    printf("compare(%u,%u)=%d\n",newIndex,oldIndex,result);
    return result;
}
#endif // DEBUG

/* void searchRepeat()
{
    unsigned newIndex,left,right,pointer,oldIndex, test;
    for(newIndex=0; newIndex<stringSize; newIndex++)
    {
        left=0;
        right=stringSize-1;
        pointer=left+(right-left)/2;
        while(1)
        {
            offsetInArray=pointer/(1<<30);
            offsetInFile=pointer%(1<<30)*sizeof(int);
            fseek(arrayFile[offsetInArray],offsetInFile,SEEK_SET);
            fread(&oldIndex,sizeof(int),1,arrayFile[offsetInArray]);
            test=compare(newIndex,oldIndex);
            if(abs(test)>1) {}
        }
    }
}
*/

int main(int argc,char *argv[])
{
    FILE *stringfile=tmpfile();
    int a=0;
    fprintf(stringfile,"olleh");
    stringFileOffset=0;
    stringSize=5;
    stringFile=stringfile;
    FILE *arrayfile=fopen("a.txt","w+b");
    arrayFile[0]=arrayfile;
    blockArray=malloc(sizeof(int));
    blockArray[0]=4;
    sizeBlockArray=1;
    sortArray();
    fseek(arrayfile,0,SEEK_SET);
    for(int b=0; b<5; b++)
    {
        fread(&a,sizeof(int),1,arrayfile);
        printf("%d\n",a);
    }
    return 0;
}
