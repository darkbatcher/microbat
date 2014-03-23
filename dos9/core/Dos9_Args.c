/*
 *
 *   Dos9 - A Free, Cross-platform command prompt - The Dos9 project
 *   Copyright (C) 2010-2014 DarkBatcher
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>
#include <libDos9.h>

#include "Dos9_Core.h"

//#define DOS9_DBG_MODE
#include "Dos9_Debug.h"

char* Dos9_GetNextParameter(char* lpLine, char* lpResponseBuffer, int iLength)
/* determines wheter a paramater follows the position lpLinLIBDOS9LIBDOS9LIBDOS9LIBDOS9e.
 *
 * lpLine : A pointer to where to seek a parameter
 * lpResponse : A buffer to store the parameter
 * iLenght : The maximum length to be stored in lpResponse
 *
 * return : the part after the parameter or null if no parameter has been found
 *
 */
 {
     ESTR* lpParameter=Dos9_EsInit();

     lpLine=Dos9_GetNextParameterEs(lpLine, lpParameter);
     strncpy(lpResponseBuffer, Dos9_EsToChar(lpParameter), iLength);
     lpResponseBuffer[iLength-1]='\0';

     Dos9_EsFree(lpParameter);
     return lpLine;
 }

/* the returning pointer is on the parenthesis
   note that the lpbkInfo->lpEnd may be NULL
   its means that the end of the block is the full
   line */
char* Dos9_GetNextBlock(char* lpLine, BLOCKINFO* lpbkInfo)
{
    char* lpBlockEnd;

    lpLine=Dos9_SkipBlanks(lpLine);

    lpBlockEnd=Dos9_GetNextBlockEnd(lpLine);

    if (*lpLine=='(')
        lpLine++;

    if (lpBlockEnd == NULL) {

        lpBlockEnd=lpLine;

        /* go to the end of line */
        while (*lpBlockEnd!='\n'
               && *lpBlockEnd!='\0' )
                lpBlockEnd++;

    }

    lpbkInfo->lpBegin=lpLine;

    lpbkInfo->lpEnd=lpBlockEnd;

    return lpBlockEnd;

}

char* Dos9_GetNextBlockEs(char* lpLine, ESTR* lpReturn)
{
    char* lpNext;
    BLOCKINFO bkInfo;

    size_t iNbBytes;

    lpNext = Dos9_GetNextBlock(lpLine, &bkInfo);

    iNbBytes = bkInfo.lpEnd - bkInfo.lpBegin;
    Dos9_EsCpyN(lpReturn, bkInfo.lpBegin, iNbBytes);

    /* replace delayed expansion */
    Dos9_DelayedExpand(lpReturn, bDelayedExpansion);

    /* remove escape characters */
    Dos9_UnEscape(Dos9_EsToChar(lpReturn));

    return lpNext+1;

}

char* Dos9_GetNextParameterEs(char* lpLine, ESTR* lpReturn)
{
     char cChar=' ';

     size_t iSize;

     char *lpBegin,
          *lpEnd=NULL;

     lpLine=Dos9_SkipBlanks(lpLine);

     if (*lpLine=='"') {

         cChar='"';
         lpLine++;

     } else if (*lpLine=='\'') {

         cChar='\'';
         lpLine++;

     }

     if (!*lpLine) return NULL;

     lpBegin=lpLine;

     while ((lpEnd=Dos9_SearchChar(lpLine, cChar))) {

        if (cChar==' ') {

            lpLine=lpEnd;
            break;

        }

        lpLine=lpEnd+1;

        if (*lpLine=='\t'
            || *lpLine==' '
            || *lpLine=='\0')
              break;

     }

     if (lpEnd == NULL) {

        Dos9_EsCpy(lpReturn, lpBegin);

        while (*lpLine) lpLine++;


     } else {

        iSize=lpEnd-lpBegin;
        Dos9_EsCpyN(lpReturn, lpBegin, iSize);

     }

     /* expand delayed expand variable */
     Dos9_DelayedExpand(lpReturn, bDelayedExpansion);

     /* remove escape characters */
     Dos9_UnEscape(Dos9_EsToChar(lpReturn));

     return lpLine;
}

int   Dos9_GetParamArrayEs(char* lpLine, ESTR** lpArray, size_t iLenght)
/*
    gets command-line argument in an array of extended string
*/
{
    size_t iIndex=0;
    ESTR* lpParam=Dos9_EsInit();
    ESTR* lpTemp=Dos9_EsInit();
    char* lpNext;

    while ((iIndex < iLenght) && (lpNext = Dos9_GetNextParameterEs(lpLine, lpParam))) {

        while (*lpLine=='\t' || *lpLine==' ') lpLine++;

        if (*lpLine == '"') {

            /* if the first character are '"', then
               report it back in the command arguments,
               since some microsoft commands would not
               work without these */

            Dos9_EsCpy(lpTemp, "\"");
            Dos9_EsCatE(lpTemp, lpParam);
            Dos9_EsCat(lpTemp, "\"");

            Dos9_EsCpyE(lpParam, lpTemp);

        }


        lpArray[iIndex]=lpParam;

        Dos9_DelayedExpand(lpParam, bDelayedExpansion);

        lpParam=Dos9_EsInit();

        lpLine=lpNext;

        iIndex++;
    }

    Dos9_EsFree(lpParam);
    Dos9_EsFree(lpTemp);


    while (iIndex < iLenght) {

        lpArray[iIndex] = NULL;

        iIndex++;

    }

    return 0;
}

LIBDOS9 char* Dos9_GetEndOfLine(char* lpLine, ESTR* lpReturn)
/* this returns fully expanded line from the lpLine Buffer */
{

    Dos9_EsCpy(lpReturn, lpLine); /* Copy the content of the line in the buffer */
    Dos9_DelayedExpand(lpReturn, bDelayedExpansion); /* Expands the content of the specified  line */

    Dos9_UnEscape(Dos9_EsToChar(lpReturn));

    return NULL;
}