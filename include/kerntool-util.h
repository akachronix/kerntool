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
#include <stdbool.h>

void detect_jailbreak(FILE* stream, char* buffer);
int newlines_in_file(FILE* fp);
int newlines_in_string(const char* s);
size_t bytes_in_file(FILE* fp);
bool does_file_exist(const char* filename);

#endif