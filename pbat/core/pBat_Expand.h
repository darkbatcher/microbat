/*
 *
 *   pBat - A Free, Cross-platform command prompt - The pBat project
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
#ifndef PBAT_EXPAND_H
#define PBAT_EXPAND_H


void pBat_ReplaceVars(ESTR* lpEsStr);
void pBat_ExpandSpecialVar(ESTR* ptrCommandLine, ESTR** buf);
void pBat_ExpandVar(ESTR* ptrCommandLine, char cDelimiter, ESTR** buf);
void pBat_DelayedExpand(ESTR* ptrCommandLine, char cEnableDelayedExpansion);

void  pBat_RemoveEscapeChar(char* lpLine);
char* pBat_StrToken(char* lpString, char cToken);

#endif