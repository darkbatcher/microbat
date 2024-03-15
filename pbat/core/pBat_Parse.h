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

#ifndef PBAT_PARSE_H
#define PBAT_PARSE_H

#include <libpBat.h>
#include "pBat_Core.h"

/* A structure to store command line
 * These information are stored in two different ways:
 * - Normal line : part of a normal line
 * - Blocks of commands : blocks of commands defined by usi braces
 */

typedef struct PARSED_STREAM {
	char cOutputMode; /* the oupout mode of stdout */
	char cErrorMode; /* the output mode of stderr */
	char cRedir; /* if we have 2>&1 or 1>&2 */
	char* lpOutputFile;
	char* lpErrorFile;
	char* lpInputFile;
} PARSED_STREAM;

typedef struct PARSED_LINE {
	ESTR* lpCmdLine;
	struct PARSED_STREAM* sStream;
	char cNodeType;
	struct PARSED_LINE* lppsNode;
} PARSED_LINE;

#define PARSED_STREAM_STDOUT2STDERR   PBAT_STREAM_SUBST_FERROR
#define PARSED_STREAM_STDERR2STDOUT   PBAT_STREAM_SUBST_FERROR

#define PARSED_STREAM_NODE_NONE 0x00
#define PARSED_STREAM_NODE_YES 0x01
#define PARSED_STREAM_NODE_NOT 0x02
#define PARSED_STREAM_NODE_PIPE 0x03
#define PARSED_STREAM_NODE_RESET -1

#define PARSED_STREAM_MODE_TRUNCATE PBAT_STREAM_MODE_TRUNCATE

PARSED_LINE* pBat_ParseLine(ESTR* lpLine);

PARSED_STREAM* pBat_ParseOutput(ESTR* lpesLine);
PARSED_LINE* pBat_ParseOperators(ESTR* lpesLine);

PARSED_LINE* pBat_AllocParsedLine(PARSED_LINE* lppsStream);
PARSED_STREAM* pBat_AllocParsedStream(void);

void pBat_FreeParsedLine(PARSED_LINE* lppsStream);
void pBat_FreeParsedStream(PARSED_STREAM* lppssStart);
PARSED_STREAM* pBat_DuplicateParsedStream(PARSED_STREAM* stream);

#define pBat_FreeLine(lpssStreamStart) pBat_FreeParsedLine(lpssStreamStart)

#endif // PBAT_PARSE_H
