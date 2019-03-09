#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static size_t bytes_in_file(FILE* fp) {
	// seek to end of the file
	fseek(fp, 0, SEEK_END);

	// grab the position
	size_t sz = ftell(fp);

	// seek back to the beginning
	rewind(fp);	

	return sz;
}

int main(int argc, const char* argv[], char **envp)
{
	fprintf(stdout, "kerntool\n");
	fprintf(stdout, "by chronix\n");
	fprintf(stdout, "https://github.com/akachronix/kerntool\n");
	fprintf(stdout, "\n");

	// debug info
	#ifdef KERNTOOL_DEBUG
		fprintf(stdout, "[DEBUG] parsing command line args\n");
	#endif
	
	// check if we have arguments
	if (argc < 2) {
		return -1;
	}

	// --offsets argument
	if (strcmp(argv[1], "--offsets") == 0) {
		// debug info
		#ifdef KERNTOOL_DEBUG
			fprintf(stdout, "[DEBUG] user selected --offsets, attempting to open file\n");
		#endif

		// open /jb/offsets.plist and do some error-handling
		FILE* fp = fopen("/jb/offsets.plist", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/jb/offsets.plist\" successfully\n");
			return -1;
		}

		// debug info
		#ifdef KERNTOOL_DEBUG
			fprintf(stdout, "[DEBUG] bytes in /jb/offsets.plist: %lu\n", bytes_in_file(fp));
		#endif

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

		// output the offset.plist
		fprintf(stdout, "%s\n", offsets);

		// close file and clean up our buffer
		fclose(fp);
		free(offsets);
	}

	// --kernel-slide argument
	if (strcmp(argv[1], "--kernel-slide") == 0) {
		// debug info
		#ifdef KERNTOOL_DEBUG
			fprintf(stdout, "[DEBUG] user selected --kernel-slide, attempting to open file\n");
		#endif

		// open /tmp/slide.txt and do some error-handling
		FILE* fp = fopen("/tmp/slide.txt", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/tmp/slide.txt\" successfully\n");
			return -1;
		}

		// debug info
		#ifdef KERNTOOL_DEBUG
			fprintf(stdout, "[DEBUG] bytes in /tmp/slide.txt: %lu\n", bytes_in_file(fp));
		#endif

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

	return 0;
}
