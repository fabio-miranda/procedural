// textfile.h: interface for reading and writing text files
// www.lighthouse3d.com
//
// You may use these functions freely.
// they are provided as is, and no warranties, either implicit,
// or explicit are given
//////////////////////////////////////////////////////////////////////

#ifndef TextFile_H
#define TextFile_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GL/glew.h"

char *textFileRead(char *fn);
int textFileWrite(char *fn, char *s);
void printInfoLog(GLhandleARB obj);

#endif