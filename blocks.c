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

unsigned _stdcall
#ifdef DEBUG
_getLen
#else
getLen
#endif // DEBUG
(unsigned index)
{
    /*
    Определение длины строки с помощью поиска в массиве.
    */
    unsigned pointer,left,right;
    left=0;
    right=sizeBlockArray-1;
    pointer=left+(right-left)/2;
    if(index>blockArray[right])
    {
        return 0;
    }
    else
    {
        while(1)
        {
            if(blockArray[pointer]<index)
            {
                left=pointer+1;
                pointer=left+(right-left)/2;
            }
            else
            {
                if(left==right)
                {
                    return(blockArray[left]-index+1);
                }
                else
                {
                    right=pointer;
                    pointer=left+(right-left)/2;
                }
            }
        }
    }
}

#ifdef DEBUG
unsigned _stdcall getLen(unsigned index)
{
    unsigned result=_getLen(index);
    printf("getLen(%u)=%u\n",index,result);
    return result;
}
#endif // DEBUG
