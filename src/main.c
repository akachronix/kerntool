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

#if defined(__linux__) || defined(__APPLE__)
	#include <sys/utsname.h>
#endif

#include "kerntool-conio.h"
#include "kerntool-info.h"
#include "kerntool-util.h"

int main(int argc, const char* argv[]) {

	char jailbreak[8];

	version(stdout);
	detect_jailbreak(stdout, jailbreak);

	if (argc > 1) {

		if (strcmp(argv[1], "--kernel-slide") == 0) {

			if (strcmp(jailbreak, "unc0ver") == 0) {

				fprintf(stdout, "[*] Opening \"/tmp/slide.txt\"\n");

				FILE* fp = fopen("/tmp/slide.txt", "r");
				if (fp == NULL) {
					
					fprintf(stderr, "[ERROR] Could not open \"/tmp/slide.txt\" successfully\n\n");
					return -1;
				}

				fprintf(stdout, "[*] Opened \"/tmp/slide.txt\" successfully\n");
				fprintf(stdout, "[*] Copying files contents into a string\n");

				size_t kslide_size = sizeof(char) * bytes_in_file(fp) + 0;
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

			else {

				fprintf(stdout, "[ERROR] This feature does not work on %s!\n\n", jailbreak);
			}
		}

		else if (strcmp(argv[1], "--cydia-log") == 0) {

			bool cydia_installed = does_file_exist("/Applications/Cydia.app");

			if (cydia_installed) {

				fprintf(stdout, "[*] Cydia is installed\n");
				fprintf(stdout, "[*] Opening \"cydia.log\"\n");

				FILE* fp = fopen("/tmp/cydia.log", "r");
				if (fp == NULL) {

					fprintf(stderr, "[ERROR] Could not open \"cydia.log\" successfully\n\n");
					return -1;
				}

				fprintf(stdout, "[*] Opened \"cydia.log\" successfully\n");
				fprintf(stdout, "[*] Copying files contents into a string\n");

				size_t cydia_log_size = sizeof(char) * bytes_in_file(fp) + 1;
				char cydia_log[cydia_log_size];

				cydia_log[cydia_log_size] = '\0';

				char c;
				int i = 0;

				while ((c = fgetc(fp)) != EOF) {

					cydia_log[i] = c;
					++i;
				}

				fprintf(stdout, "[*] Parsing string\n");

				int cydia_log_newlines = newlines_in_string(cydia_log);
				char* cydia_log_lines[cydia_log_newlines];

				cydia_log_lines[0] = strtok(cydia_log, "\n");
				char* token = cydia_log_lines[0];

				i = 0;

				while (token != NULL) {

					token = strtok(NULL, "\n");
					cydia_log_lines[i] = token;
					++i;
				}

				fprintf(stdout, "[*] Done parsing!\n\n");
				fprintf(stdout, "[*] Pressing any key shows the next line in the file\n\n");

				for (i = 0; i < cydia_log_newlines - 1; ++i) {

					fprintf(stdout, "%s\n", cydia_log_lines[i]);
					getch();
				}

				fclose(fp);
			}

			else {

				fprintf(stdout, "[ERROR] Cydia is not installed!\n\n");
				return -1;
			}
		}

		else if (strcmp(argv[1], "--offsets") == 0) {

			if (strcmp(jailbreak, "unc0ver") == 0) {

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
			
			else {

				fprintf(stdout, "[ERROR] This feature does not work on %s!\n\n", jailbreak);
			}
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
			fprintf(stdout, "%s %s %s %s\n\n", _utsname.sysname, _utsname.release, _utsname.version, _utsname.machine);
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

		else {

			help(stdout);
			return -1;
		}
	}

	return 0;
}
