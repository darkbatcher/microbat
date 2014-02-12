#ifndef DOS9_SCRIPTCOMMAND_H
#define DOS9_SCRIPTCOMMAND_H

#include "Dos9_CmdLib.h"

int Dos9_CmdEcho(char* lpLine);
int Dos9_CmdPause(char* lpLine);

int Dos9_CmdSet(char* lpLine);
int Dos9_CmdSetS(char* lpLine);
int Dos9_CmdSetP(char* lpLine);
int Dos9_CmdSetA(char* lpLine, int bFloats);
int Dos9_CmdSetEvalFloat(ESTR* lpExpression);
int Dos9_CmdSetEvalInt(ESTR* lpExpression);

int Dos9_CmdBlock(char* lpLine);

int Dos9_CmdExit(char* lpLine);
int Dos9_CmdSetLocal(char* lpLine);
int Dos9_CmdHelp(char* lpLine);

int Dos9_CmdRem(char* lpLine);
int Dos9_CmdTitle(char* lpLine);
int Dos9_CmdCls(char* lpLine);

int Dos9_CmdColor(char* lpLine);
int Dos9_CmdGoto(char* lpLine);

int Dos9_CmdType(char* lpLine);

int Dos9_CmdCd(char* lpLine);

int Dos9_CmdDir(char* lpLine);

#endif
