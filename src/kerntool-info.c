//
// kerntool-info.c
// kerntool
// by chronix
// 
// licensed under wtfpl
//
// credits in README.md
//

#include "kerntool-info.h"

void version(FILE* stream) {

	fprintf(stdout, "\n");
	fprintf(stdout, "kerntool v0.4\n");
	fprintf(stdout, "by chronix\n");
	fprintf(stdout, "https://github.com/akachronix/kerntool\n");
	fprintf(stdout, "\n");
}

void help(FILE* stream) {

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
