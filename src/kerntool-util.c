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

void detect_jailbreak(FILE* stream, char* jb_buffer) {

	fprintf(stream, "[*] Detecting jailbreak\n");

	if (does_file_exist("/.installed_home_depot"))
		sprintf(jb_buffer, "Home Depot / Phoenix");
	
	else if (does_file_exist("/untether/expl.js"))
		sprintf(jb_buffer, "EtasonJB");
	
	else if (does_file_exist("/.installed_unc0ver"))
		sprintf(jb_buffer, "unc0ver");
	
	else if (does_file_exist("/.bootstrapped_electra"))
		sprintf(jb_buffer, "Electra");
	
	else if (does_file_exist("/chimera/"))
		sprintf(jb_buffer, "Chimera");
	
	else if (does_file_exist("/panguaxe.installed"))
		sprintf(jb_buffer, "Pangu7");

	else {
		
		sprintf(jb_buffer, "NULL");
		fprintf(stream, "[*] No jailbreak detected! (or your jailbreak hasn't been added for support yet!)\n\n");

		return;
	}

	fprintf(stream, "[*] Detected %s!\n\n", jb_buffer);
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
