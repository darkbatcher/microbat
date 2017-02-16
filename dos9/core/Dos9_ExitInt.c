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

#include "Dos9_Core.h"


void Dos9_Exit(void)
{
    printf("Exiting Dos9\n");
	Dos9_FreeCommandList(lpclCommands);
	Dos9_FreeStreamStack(lppsStreamStack);
	Dos9_FreeLocalBlock(lpvLocalVars);
	Dos9_EnvFree(lpeEnv);

	if (iInputD)
		close(iInputD);

	if (iOutputD)
		close(iOutputD);


    printf("Waiting for all threads\n");
	Dos9_WaitForAllThreads();

}
