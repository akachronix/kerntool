//
// kerntool-util.c
// kerntool
// by chronix
// 
// licensed under wtfpl
//
// credits in README.md
//

#include "kerntool-util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int newlines_in_file(FILE* fp) {

	size_t buffer_size = sizeof(char) * bytes_in_file(fp) + 1;
	char* buffer = (char*)malloc(buffer_size);

	buffer[buffer_size] = '\0';		

	char c;
	int i = 0;

	while ((c = fgetc(fp)) != EOF) {
		buffer[i] = c;
		++i;
	}

	int buffer_newlines = 0;
	for (i = 0; i < buffer_size; ++i) {
		if (buffer[i] == '\n') {
			++buffer_newlines;
		}
	}

	free(buffer);
	return buffer_newlines;
}

int newlines_in_string(const char* s) {

	int buffer_newlines = 0;
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] == '\n') {
			++buffer_newlines;
		}
	}

	return buffer_newlines;
}

size_t bytes_in_file(FILE* fp) {

	fseek(fp, 0, SEEK_END);
	size_t sz = ftell(fp);
	rewind(fp);	

	return sz;
}

bool does_file_exist(const char* filename) {

	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return false;
	}

	fclose(fp);
	return true;
}
