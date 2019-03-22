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

#include "kerntool-util.h"
#include "kerntool-conio.h"

#if defined(__APPLE__)
	#include <mach/mach.h>
	#include <sys/utsname.h>
#endif

#if defined(__linux__)
	#include <sys/utsname.h>
#endif

static void version(FILE* stream) {

	fprintf(stdout, "\n");
	fprintf(stdout, "kerntool v0.2\n");
	fprintf(stdout, "by chronix\n");
	fprintf(stdout, "https://github.com/akachronix/kerntool\n");
	fprintf(stdout, "\n");
}

static void help(FILE* stream) {

	fprintf(stream, "Valid arguments --\n");
	fprintf(stream, "  --kernel-slide | reads the kernel slide from a file dropped by unc0ver and spits its contents out to console (DO NOT EXPECT THIS TO WORK IF YOU'RE USING ELECTRA!)\n");
	fprintf(stream, "  --offsets      | reads offsets from offsets.plist and spits their contents out to console\n");
	fprintf(stream, "  --block-domain | enter a domain to block using hosts file\n");
	fprintf(stream, "  --hosts        | reads from /etc/hosts and spits its contents out to console\n");
	fprintf(stream, "  --hostname     | gets device name\n");
	fprintf(stream, "  --uname        | gets kernel and general device information\n");
	fprintf(stream, "  --fstab        | reads from /etc/fstab and spits its contents out to console\n");
	fprintf(stream, "  --version      | get the version of this tool\n");
	fprintf(stream, "  --help         | spits this helpful screen out\n");
	fprintf(stream, "  --author       | get information about me ;)\n");
	fprintf(stream, "  --about        | a little bit of background information about this project\n");
	fprintf(stream, "  --credits      | a list of the other people that have contributed in some way to this project\n");
	fprintf(stream, "\n");
}

int main(int argc, const char* argv[]) {

	version(stdout);

	// check if we have arguments
	if (argc < 2) {

		help(stdout);
		return -1;
	}

	// --kernel-slide argument
	else if (strcmp(argv[1], "--kernel-slide") == 0) {

		// let the world know we're opening a file
		fprintf(stdout, "[*] Opening \"/tmp/slide.txt\"\n");

		// open /tmp/slide.txt and do some error-handling
		FILE* fp = fopen("/tmp/slide.txt", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/tmp/slide.txt\" successfully\n\n");
			return -1;
		}

		// progess report
		fprintf(stdout, "[*] Opened \"/tmp/slide.txt\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

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

		// output some stuff
		fprintf(stdout, "[*] Done parsing!\n\n");

		// output the kernel slide
		fprintf(stdout, "kernel slide: %s\n", kslide);

		// close file and clean up our buffer
		fclose(fp);
		free(kslide);
	}

	// --offsets argument
	else if (strcmp(argv[1], "--offsets") == 0) {

		// let the world know we're opening a file
		fprintf(stdout, "[*] Opening \"/jb/offsets.plist\"\n");

		// open /jb/offsets.plist and do some error-handling
		FILE* fp = fopen("/jb/offsets.plist", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/jb/offsets.plist\" successfully\n\n");
			return -1;
		}

		// progess report
		fprintf(stdout, "[*] Opened \"/jb/offsets.plist\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

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

		// progress report
		fprintf(stdout, "[*] Parsing string\n");

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

		// output some stuff
		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

		// finally, output the contents of the file line by line
		for (i = 0; i < offsets_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", offsets_lines[i]);
			getch();
		}

		// close file and clean up our buffer
		fclose(fp);
		free(offsets);
	}

	// --block-domain argument
	else if (strcmp(argv[1], "--block-domain") == 0) {

		// open /etc/hosts and do some error-handling
		FILE* fp = fopen("/etc/hosts", "a+");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/hosts\" successfully (try running as root, I need write access!)\n\n");
			return -1;
		}

		// create a string to hold the domain name
		char* domain;

		// if the user specified using cli args, copy the arg into the string
		if (argc > 2) {
			size_t domain_size = sizeof(char) * strlen(argv[2]) + 1;
			domain = (char*)malloc(domain_size);
			memcpy(domain, argv[2], domain_size);
		}
		
		// otherwise, prompt for the domain here
		else {
			size_t domain_size = sizeof(char) + 63 + 1;
			domain = (char*)malloc(domain_size);

			fprintf(stdout, "[*] Enter domain to block: ");
			fscanf(stdin, "%63s", domain);

			fprintf(stdout, "\n");
		}

		// add the entry to the hosts file
		fprintf(stdout, "[*] Adding entry to block domain \"%s\" to hosts file\n", domain);
		fprintf(fp, "\n# Added by kerntool\n0 %s\n", domain);

		// we're done
		fprintf(stdout, "[*] Complete!\n\n");

		// close the file and clean up our buffer
		fclose(fp);
		free(domain);
	}

	// --hosts argument
	else if (strcmp(argv[1], "--hosts") == 0) {
		
		// let the world know we're opening a file
		fprintf(stdout, "[*] Opening \"/etc/hosts\"\n");

		// open /etc/hosts and do some error-handling
		FILE* fp = fopen("/etc/hosts", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/hosts\" successfully\n\n");
			return -1;
		}

		// progess report
		fprintf(stdout, "[*] Opened \"/etc/hosts\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

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

		// progress report
		fprintf(stdout, "[*] Parsing string\n");

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

		// output some stuff
		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

		// finally, output the contents of the file line by line
		for (i = 0; i < hosts_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", hosts_lines[i]);
			getch();
		}

		// close file and clean up our buffer;
		fclose(fp);
		free(hosts);
	}

	else if (strcmp(argv[1], "--hostname") == 0) {
		
		// let the whole world know that we're getting hardware info
		fprintf(stdout, "[*] Getting hardware info\n");

		// create utsname struct
		struct utsname _utsname;

		// get hardware info and fill the struct and do some error-handling
		if (uname(&_utsname) == -1) {
			fprintf(stderr, "[ERROR] couldn't load hardware info\n\n");
			return -1;
		}

		// progress update
		fprintf(stdout, "[*] Successfully retrieved hardware info\n\n");
		
		// spit out info from struct to console
		fprintf(stdout, "Hostname: %s\n\n", _utsname.nodename);
	}

	// --uname argument
	else if (strcmp(argv[1], "--uname") == 0) {

		// let the whole world know that we're getting hardware info
		fprintf(stdout, "[*] Getting hardware info\n");

		// create utsname struct
		struct utsname _utsname;

		// get hardware info and fill the struct and do some error-handling
		if (uname(&_utsname) == -1) {
			fprintf(stderr, "[ERROR] couldn't load hardware info\n\n");
			return -1;
		}

		// progress update
		fprintf(stdout, "[*] Successfully retrieved hardware info\n\n");
		
		// spit out info from struct to console
		fprintf(stdout, "%s %s %s %s\n\n", 
			_utsname.sysname,
			_utsname.release,
			_utsname.version,
			_utsname.machine
		);
	}

	// --fstab argument
	else if (strcmp(argv[1], "--fstab") == 0) {
		// let the world know we're opening a file
		fprintf(stdout, "[*] Opening \"/etc/fstab\"\n");

		// open /etc/fstab and do some error-handling
		FILE* fp = fopen("/etc/fstab", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/fstab\" successfully\n\n");
			return -1;
		}

		// progess report
		fprintf(stdout, "[*] Opened \"/etc/fstab\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

		// calculate the size of buffer we need and allocate that block of memory
		size_t fstab_size = sizeof(char) * bytes_in_file(fp) + 1;
		char* fstab = (char*)malloc(fstab_size);

		// set last character as null
		fstab[fstab_size] = '\0';

		// create a character buffer and iterator
		char c;
		int i = 0;

		// grab data from /etc/hosts character by character
		while ((c = fgetc(fp)) != EOF) {
			fstab[i] = c;
			++i;
		}

		// progress report
		fprintf(stdout, "[*] Parsing string\n");

		// get the amount of newlines
		int fstab_newlines = newlines_in_string(fstab);
		
		// create an array of strings with each index referring to a line
		char* fstab_lines[fstab_newlines];

		// tokenize the string for the first time (getting ready to loop through)
		fstab_lines[0] = strtok(fstab, "\n");
		char* token = fstab_lines[0];

		// reset iterator variable
		i = 0;

		// tokenize the string more
		while (token != NULL) {
			token = strtok(NULL, "\n");
			fstab_lines[i] = token;
			++i;
		}

		// output some stuff
		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

		// finally, output the contents of the file line by line
		for (i = 0; i < fstab_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", fstab_lines[i]);
			getch();
		}

		// close file and clean up our buffer;
		fclose(fp);
		free(fstab);
	}

	// --version argument
	else if (strcmp(argv[1], "--version") == 0) {
		// do nothing as the version string has already been output
	}

	// --help argument
	else if (strcmp(argv[1], "--help") == 0) {
		help(stdout);
	}

	// --author argument
	else if (strcmp(argv[1], "--author") == 0) {

		// quick little paragraph, ya know
		fprintf(stdout, "So as you know, my name is Chronix.\n");
		fprintf(stdout, "I make music as well as programming so you should check it out.\n");
		fprintf(stdout, "I'll *carefully* shove my links down here.\n\n");
		fprintf(stdout, "YouTube: \thttps://www.youtube.com/channel/UCEj2uj_VZYYOa8tIBb63tUg\n");
		fprintf(stdout, "Spotify: \thttps://open.spotify.com/artist/2mZ7TyrKsCMtAeppYESQQJ\n");
		fprintf(stdout, "iTunes: \thttps://itunes.apple.com/us/artist/chronix/374153691\n");
		fprintf(stdout, "Instagram: \thttps://www.instagram.com/akachronix\n");
		fprintf(stdout, "Snapchat: \thttps://www.snapchat.com/add/aka.chronix\n");
		fprintf(stdout, "\n");
	}

	// --about argument
	else if (strcmp(argv[1], "--about") == 0) {
		
		// history about myself, ig
		fprintf(stdout, "I've been interested in jailbreaking for a while and started during iOS 4.\n");
		fprintf(stdout, "Back then, I was a kid and had no idea what the fuck I was doing and just installed tweaks willy-nilly.\n");
		fprintf(stdout, "I became interested in development around the age of 10 and had learned C++ by 13.\n");
		fprintf(stdout, "I am just now beginning to get into iOS development and this is an extremely easy way to get into it.\n");
		fprintf(stdout, "As of now, I don't really know what I want to do with my life but I hope that I can do something that I love eventually.\n");
		fprintf(stdout, "I started this project out of boredom; to test my abilities I guess.\n");
		fprintf(stdout, "This is heavily inspired by jtool, a project by Jonathan Levin.\n");
		fprintf(stdout, "Hopefully, I learn some valuable information from working on this project.\n");
		fprintf(stdout, "Thanks for reading this wall of text. -chronix\n");
	}

	// --credits argument
	else if (strcmp(argv[1], "--credits") == 0) {

		// a list of others that have contributed something to this project
		fprintf(stdout, "chronix  - kerntool\n");
		fprintf(stdout, "uroboro  - theos\n");
		fprintf(stdout, "muirey03 - entitlements\n");
		fprintf(stdout, "pwn20wnd - unc0ver jailbreak\n");
		fprintf(stdout, "sbingner - unc0ver jailbreak\n");
		fprintf(stdout, "\n");
	}

	// undefined argument
	else {
		help(stdout);
		return -1;
	}

	return 0;
}