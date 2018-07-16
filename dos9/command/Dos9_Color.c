/*
 *
 *   Dos9 - A Free, Cross-platform command prompt - The Dos9 project
 *   Copyright (C) 2010-2016 Romain GARBI
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#include <libDos9.h>

#include "../core/Dos9_Core.h"

#include "Dos9_Color.h"

#include "../lang/Dos9_Lang.h"
#include "../lang/Dos9_ShowHelp.h"

// #define DOS9_DBG_MODE
#include "../core/Dos9_Debug.h"
#include "../errors/Dos9_Errors.h"

#define TO_CHAR(a) (0x00FF & (a))
#define HWORD(a) ((0xF0 & (a)) >> 4)
#define LWORD(a) (0xF & (a))

int Dos9_GetColorCode(char* lpArg)
{
    int back=DOS9_GET_BACKGROUND_(colColor),
        fore; /* back and foreground */
    int i=strlen(lpArg);

    if (i > 2
        || i <= 0)
        return -1;

    if (i > 1) {

        switch (tolower(*lpArg)) {

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            back = *lpArg - '0';
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            back = 10 + tolower(*lpArg) - 'a';
            break;

        case '.':
            back = DOS9_GET_BACKGROUND_(colColor);
            break;

        default:
            return -1;

        }

        lpArg ++;
    }

    switch (tolower(*lpArg)) {

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        fore = *lpArg - '0';
        break;

    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
        fore = 10 + tolower(*lpArg) - 'a';
        break;

    case '.':
        fore = DOS9_GET_FOREGROUND_(colColor);
        break;

    default:
        return -1;

    }

    return fore | (back << 4);

}

int Dos9_CmdColor(char* lpLine)
{
	char lpArg[4];
	int code;

	if (Dos9_GetNextParameter(lpLine+5, lpArg, 4)) {

		if (!strcmp(lpArg, "/?")) {

			Dos9_ShowInternalHelp(DOS9_HELP_COLOR);

		} else {

			if ((code = Dos9_GetColorCode(lpArg)) == -1
                || (HWORD(code) == LWORD(code))) {

                Dos9_ShowErrorMessage(DOS9_UNEXPECTED_ELEMENT, lpArg, 0);
                return DOS9_UNEXPECTED_ELEMENT;

            }

            colColor = code;
			Dos9_SetConsoleColor(colColor);

		}

		return DOS9_NO_ERROR;

	}

	colColor=DOS9_COLOR_DEFAULT;
	Dos9_SetConsoleColor(DOS9_COLOR_DEFAULT);

	return DOS9_NO_ERROR;
}
