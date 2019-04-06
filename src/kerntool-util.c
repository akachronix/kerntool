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

#if 0
// might be used later but theos is a bitch and won't compile with unused symbols
int newlines_in_file(FILE* fp) {

	// find the size of buffer we need to create
	size_t buffer_size = sizeof(char) * bytes_in_file(fp) + 1;
	char* buffer = (char*)malloc(buffer_size);
			
	// set last character as null
	buffer[buffer_size] = '\0';		

	// create a character buffer and iterator
	char c;
	int i = 0;

	// grab data from file character by character
	while ((c = fgetc(fp)) != EOF) {
		buffer[i] = c;
		++i;
	}

	// and finally, find the amount of newlines
	int buffer_newlines = 0;
	for (i = 0; i < buffer_size; ++i) {
		if (buffer[i] == '\n') {
			++buffer_newlines;
		}
	}

	// clean up
	free(buffer);

	return buffer_newlines;
}
#endif

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