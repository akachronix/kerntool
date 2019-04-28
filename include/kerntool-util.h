//
// kerntool-util.h
// kerntool
// by chronix
// 
// licensed under wtfpl
//
// credits in README.md
//

#ifndef KERNTOOL_UTIL_H
#define KERNTOOL_UTIL_H

#include <stdio.h>

int newlines_in_file(FILE* fp);
int newlines_in_string(const char* s);
size_t bytes_in_file(FILE* fp);

#endif