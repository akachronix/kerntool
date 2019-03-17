//
// main.c
// kerntool
// by chronix
// 
// licensed under wtfpl
//
// credits in README.md
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "kerntool-conio.h"

#if defined(__APPLE__)
	#include <mach/mach.h>
	#include <sys/utsname.h>
#endif

static size_t bytes_in_file(FILE* fp) {

	// seek to end of the file
	fseek(fp, 0, SEEK_END);

	// grab the position
	size_t sz = ftell(fp);

	// seek back to the beginning
	rewind(fp);	

	return sz;
}

/* might be used later but theos is a bitch and won't compile with unused symbols
static int newlines_in_file(FILE* fp) {

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
} */

static int newlines_in_string(const char* s) {

	int buffer_newlines = 0;
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] == '\n') {
			++buffer_newlines;
		}
	}

	return buffer_newlines;
}

static void version(FILE* stream) {

	fprintf(stdout, "kerntool\n");
	fprintf(stdout, "by chronix\n");
	fprintf(stdout, "https://github.com/akachronix/kerntool\n");
	fprintf(stdout, "\n");
}

static void help(FILE* stream) {

	fprintf(stream, "Valid arguments --\n");
	fprintf(stream, "  --offsets      | reads offsets from offsets.plist and spits their contents out to console\n");
	fprintf(stream, "  --kernel-slide | reads the kernel slide from a file dropped by unc0ver and spits its contents out to console (DO NOT EXPECT THIS TO WORK IF YOU'RE USING ELECTRA!)\n");
	fprintf(stream, "  --hosts        | reads from /etc/hosts and spits its contents out to console\n");
	fprintf(stream, "  --uname        | gets kernel and general device information\n");
	fprintf(stream, "  --version      | get the version of this tool\n");
	fprintf(stream, "  --help         | spits this helpful screen out\n");
}

int main(int argc, const char* argv[]) {

	version(stdout);

	// check if we have arguments
	if (argc < 2) {

		help(stdout);
		return -1;
	}

	// --offsets argument
	if (strcmp(argv[1], "--offsets") == 0) {

		// open /jb/offsets.plist and do some error-handling
		FILE* fp = fopen("/jb/offsets.plist", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/jb/offsets.plist\" successfully\n");
			return -1;
		}

		// calculate the size of buffer we need and allocate that block of memory
		size_t offsets_size = sizeof(char) * bytes_in_file(fp) + 1;		
		char* offsets = (char*)malloc(offsets_size);
		
		// set last character as null
		offsets[offsets_size] = '\0';		

		// create a character buffer and iterator
		char c;
		int i = 0;

		// grab data from /jb/offsets.plist character by character
		while ((c = fgetc(fp)) != EOF) {
			offsets[i] = c;
			++i;
		}

		// get the amount of newlines
		int offsets_newlines = newlines_in_string(offsets);
		
		// create an array of strings with each index referring to a line
		char* offsets_lines[offsets_newlines];

		// tokenize the string for the first time (getting ready to loop through)
		offsets_lines[0] = strtok(offsets, "\n");
		char* token = offsets_lines[0];

		// reset iterator variable
		i = 0;

		// tokenize the string more
		while (token != NULL) {
			token = strtok(NULL, "\n");
			offsets_lines[i] = token;
			++i;
		}

		// finally, output the contents of the file line by line
		for (i = 0; i < offsets_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", offsets_lines[i]);
			getch();
		}

		// close file and clean up our buffer
		fclose(fp);
		free(offsets);
	}

	// --kernel-slide argument
	else if (strcmp(argv[1], "--kernel-slide") == 0) {

		// open /tmp/slide.txt and do some error-handling
		FILE* fp = fopen("/tmp/slide.txt", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/tmp/slide.txt\" successfully\n");
			return -1;
		}

		// calculate the size of buffer we need and allocate that block of memory
		size_t kslide_size = sizeof(char) * bytes_in_file(fp) + 1;
		char* kslide = (char*)malloc(kslide_size);

		// set last character as null
		kslide[kslide_size] = '\0';

		// create a character buffer and iterator
		char c;
		int i = 0;

		// grab data from /tmp/slide.txt character by character
		while ((c = fgetc(fp)) != EOF) {
			kslide[i] = c;
			++i;
		}

		// output the kernel slide
		fprintf(stdout, "kernel slide: %s\n", kslide);

		// close file and clean up our buffer
		fclose(fp);
		free(kslide);
	}

	// --hosts argument
	else if (strcmp(argv[1], "--hosts") == 0) {
		
		// open /etc/hosts and do some error-handling
		FILE* fp = fopen("/etc/hosts", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/hosts\" successfully\n");
			return -1;
		}

		// calculate the size of buffer we need and allocate that block of memory
		size_t hosts_size = sizeof(char) * bytes_in_file(fp) + 1;
		char* hosts = (char*)malloc(hosts_size);

		// set last character as null
		hosts[hosts_size] = '\0';

		// create a character buffer and iterator
		char c;
		int i = 0;

		// grab data from /etc/hosts character by character
		while ((c = fgetc(fp)) != EOF) {
			hosts[i] = c;
			++i;
		}

		// get the amount of newlines
		int hosts_newlines = newlines_in_string(hosts);
		
		// create an array of strings with each index referring to a line
		char* hosts_lines[hosts_newlines];

		// tokenize the string for the first time (getting ready to loop through)
		hosts_lines[0] = strtok(hosts, "\n");
		char* token = hosts_lines[0];

		// reset iterator variable
		i = 0;

		// tokenize the string more
		while (token != NULL) {
			token = strtok(NULL, "\n");
			hosts_lines[i] = token;
			++i;
		}

		// finally, output the contents of the file line by line
		for (i = 0; i < hosts_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", hosts_lines[i]);
			getch();
		}

		// close file and clean up our buffer;
		fclose(fp);
		free(hosts);
	}

	// --uname argument
	else if (strcmp(argv[1], "--uname") == 0) {

		// create utsname struct
		struct utsname _utsname;

		// get hardware info and fill the struct and do some error-handling
		if (uname(&_utsname) == -1) {
			fprintf(stderr, "[ERROR] couldn't load uname info\n");
			return -1;
		}
		
		// spit out info from struct to console
		fprintf(stdout, "%s %s %s %s %s\n", 
			_utsname.nodename,
			_utsname.sysname,
			_utsname.release,
			_utsname.version,
			_utsname.machine
		);
	}

	// --version argument
	else if (strcmp(argv[1], "--version") == 0) {
		version(stdout);
	}

	// --help argument
	else if (strcmp(argv[1], "--help") == 0) {
		help(stdout);
	}

	// undefined argument
	else {
		help(stdout);
		return -1;
	}

	return 0;
}