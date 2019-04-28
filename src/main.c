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
#include "kerntool-info.h"
#include "kerntool-util.h"

#if defined(__APPLE__)
	#include <mach/mach.h>
	#include <sys/utsname.h>
#endif

#if defined(__linux__)
	#include <sys/utsname.h>
#endif

int main(int argc, const char* argv[]) {

	version(stdout);

	if (argc < 2) {

		help(stdout);
		return -1;
	}

	else if (strcmp(argv[1], "--kernel-slide") == 0) {

		fprintf(stdout, "[*] Opening \"/tmp/slide.txt\"\n");

		FILE* fp = fopen("/tmp/slide.txt", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/tmp/slide.txt\" successfully\n\n");
			return -1;
		}

		fprintf(stdout, "[*] Opened \"/tmp/slide.txt\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

		size_t kslide_size = sizeof(char) * bytes_in_file(fp) + 1;
		char kslide[kslide_size];

		kslide[kslide_size] = '\0';

		char c;
		int i = 0;

		while ((c = fgetc(fp)) != EOF) {
			kslide[i] = c;
			++i;
		}

		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "kernel slide: %s\n", kslide);

		fclose(fp);
	}

	else if (strcmp(argv[1], "--offsets") == 0) {

		fprintf(stdout, "[*] Opening \"/jb/offsets.plist\"\n");

		FILE* fp = fopen("/jb/offsets.plist", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/jb/offsets.plist\" successfully\n\n");
			return -1;
		}

		fprintf(stdout, "[*] Opened \"/jb/offsets.plist\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

		size_t offsets_size = sizeof(char) * bytes_in_file(fp) + 1;		
		char offsets[offsets_size];
		
		offsets[offsets_size] = '\0';		

		char c;
		int i = 0;

		while ((c = fgetc(fp)) != EOF) {
			offsets[i] = c;
			++i;
		}

		fprintf(stdout, "[*] Parsing string\n");

		int offsets_newlines = newlines_in_string(offsets);
		char* offsets_lines[offsets_newlines];

		offsets_lines[0] = strtok(offsets, "\n");
		char* token = offsets_lines[0];

		i = 0;

		while (token != NULL) {
			token = strtok(NULL, "\n");
			offsets_lines[i] = token;
			++i;
		}

		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

		for (i = 0; i < offsets_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", offsets_lines[i]);
			getch();
		}

		fclose(fp);
	}

	else if (strcmp(argv[1], "--block-domain") == 0) {

		FILE* fp = fopen("/etc/hosts", "a+");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/hosts\" successfully (try running as root, I need write access!)\n\n");
			return -1;
		}

		char* domain;

		if (argc > 2) {
			size_t domain_size = sizeof(char) * strlen(argv[2]) + 1;
			domain = (char*)malloc(domain_size);
			memcpy(domain, argv[2], domain_size);
		}
		
		else {
			size_t domain_size = sizeof(char) + 63 + 1;
			domain = (char*)malloc(domain_size);

			fprintf(stdout, "[*] Enter domain to block: ");
			fscanf(stdin, "%63s", domain);

			fprintf(stdout, "\n");
		}

		fprintf(stdout, "[*] Adding entry to block domain \"%s\" to hosts file\n", domain);
		fprintf(fp, "\n# Added by kerntool\n0 %s\n", domain);

		fprintf(stdout, "[*] Complete!\n\n");

		fclose(fp);
		free(domain);
	}

	else if (strcmp(argv[1], "--hosts") == 0) {
		
		fprintf(stdout, "[*] Opening \"/etc/hosts\"\n");

		FILE* fp = fopen("/etc/hosts", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/hosts\" successfully\n\n");
			return -1;
		}

		fprintf(stdout, "[*] Opened \"/etc/hosts\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

		size_t hosts_size = sizeof(char) * bytes_in_file(fp) + 1;
		char hosts[hosts_size];

		hosts[hosts_size] = '\0';

		char c;
		int i = 0;

		while ((c = fgetc(fp)) != EOF) {
			hosts[i] = c;
			++i;
		}

		fprintf(stdout, "[*] Parsing string\n");

		int hosts_newlines = newlines_in_string(hosts);
		char* hosts_lines[hosts_newlines];

		hosts_lines[0] = strtok(hosts, "\n");
		char* token = hosts_lines[0];

		i = 0;

		while (token != NULL) {
			token = strtok(NULL, "\n");
			hosts_lines[i] = token;
			++i;
		}

		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

		for (i = 0; i < hosts_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", hosts_lines[i]);
			getch();
		}

		fclose(fp);
	}

	else if (strcmp(argv[1], "--hostname") == 0) {
		
		fprintf(stdout, "[*] Getting hardware info\n");

		struct utsname _utsname;
		if (uname(&_utsname) == -1) {
			fprintf(stderr, "[ERROR] couldn't load hardware info\n\n");
			return -1;
		}

		fprintf(stdout, "[*] Successfully retrieved hardware info\n\n");
		fprintf(stdout, "Hostname: %s\n\n", _utsname.nodename);
	}

	else if (strcmp(argv[1], "--uname") == 0) {

		fprintf(stdout, "[*] Getting hardware info\n");

		struct utsname _utsname;
		if (uname(&_utsname) == -1) {
			fprintf(stderr, "[ERROR] couldn't load hardware info\n\n");
			return -1;
		}

		fprintf(stdout, "[*] Successfully retrieved hardware info\n\n");
		fprintf(stdout, "%s %s %s %s\n\n", 
			_utsname.sysname,
			_utsname.release,
			_utsname.version,
			_utsname.machine
		);
	}

	else if (strcmp(argv[1], "--fstab") == 0) {

		fprintf(stdout, "[*] Opening \"/etc/fstab\"\n");

		FILE* fp = fopen("/etc/fstab", "r");
		if (fp == NULL) {
			fprintf(stderr, "[ERROR] Could not open \"/etc/fstab\" successfully\n\n");
			return -1;
		}

		fprintf(stdout, "[*] Opened \"/etc/fstab\" successfully\n");
		fprintf(stdout, "[*] Copying files contents into a string\n");

		size_t fstab_size = sizeof(char) * bytes_in_file(fp) + 1;
		char fstab[fstab_size];

		fstab[fstab_size] = '\0';

		char c;
		int i = 0;

		while ((c = fgetc(fp)) != EOF) {
			fstab[i] = c;
			++i;
		}

		fprintf(stdout, "[*] Parsing string\n");

		int fstab_newlines = newlines_in_string(fstab);
		char* fstab_lines[fstab_newlines];

		fstab_lines[0] = strtok(fstab, "\n");
		char* token = fstab_lines[0];

		i = 0;

		while (token != NULL) {
			token = strtok(NULL, "\n");
			fstab_lines[i] = token;
			++i;
		}

		fprintf(stdout, "[*] Done parsing!\n\n");
		fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

		for (i = 0; i < fstab_newlines - 1; ++i) {
			fprintf(stdout, "%s\n", fstab_lines[i]);
			getch();
		}

		fclose(fp);
	}

	else if (strcmp(argv[1], "--version") == 0) {
		// do nothing as the version string has already been output
	}

	else if (strcmp(argv[1], "--help") == 0) {
		help(stdout);
	}

	else if (strcmp(argv[1], "--author") == 0) {

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

	else if (strcmp(argv[1], "--about") == 0) {
		
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

	else if (strcmp(argv[1], "--credits") == 0) {

		fprintf(stdout, "chronix  - kerntool\n");
		fprintf(stdout, "uroboro  - theos\n");
		fprintf(stdout, "muirey03 - entitlements\n");
		fprintf(stdout, "pwn20wnd - unc0ver jailbreak\n");
		fprintf(stdout, "sbingner - unc0ver jailbreak\n");
		fprintf(stdout, "\n");
	}

	else {

		help(stdout);
		return -1;
	}

	return 0;
}