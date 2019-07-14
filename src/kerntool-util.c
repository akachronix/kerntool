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

void detect_jailbreak(FILE* stream, char* buffer) {

	fprintf(stream, "[*] Detecting jailbreak\n");

	bool unc0ver = does_file_exist("/.installed_unc0ver");
	bool electra = does_file_exist("/.bootstrapped_electra");
	bool chimera = does_file_exist("/chimera/");
	bool pangu7 = does_file_exist("/panguaxe");

	if (unc0ver) {
		
		sprintf(buffer, "unc0ver");
		fprintf(stream, "[*] Detected unc0ver!\n\n");
	}

	else if (electra) {
		
		sprintf(buffer, "Electra");
		fprintf(stream, "[*] Detected Electra!\n\n");
	}

	else if (chimera) {
		
		sprintf(buffer, "Chimera");
		fprintf(stream, "[*] Detected Chimera!\n\n");
	}

	else if (pangu7) {
		
		sprintf(buffer, "Pangu7");
		fprintf(stream, "[*] Detected Pangu7!\n\n");
	}

	else {
		
		sprintf(buffer, "NULL");
		fprintf(stream, "[*] No jailbreak detected! (or your jailbreak hasn't been added for support yet!)\n\n");
	}
}

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
