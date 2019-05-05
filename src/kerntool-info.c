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
	fprintf(stdout, "kerntool v0.6\n");
	fprintf(stdout, "by chronix\n");
	fprintf(stdout, "https://github.com/akachronix/kerntool\n");
	fprintf(stdout, "\n");
}

void help(FILE* stream) {

	fprintf(stream, "Valid arguments --\n\n");
	fprintf(stream, "  --kernel-slide\n\treads the kernel slide from a file dropped by unc0ver and spits its contents out to console (DO NOT EXPECT THIS TO WORK IF YOU'RE USING ELECTRA!)\n\n");
	fprintf(stream, "  --offsets\n\treads offsets from offsets.plist and spits their contents out to console\n\n");
	fprintf(stream, "  --block-domain\n\tenter a domain to block using hosts file\n\n");
	fprintf(stream, "  --hosts\n\treads from /etc/hosts and spits its contents out to console\n\n");
	fprintf(stream, "  --hostname\n\tgets device name\n\n");
	fprintf(stream, "  --uname\n\tgets kernel and general device information\n\n");
	fprintf(stream, "  --fstab\n\treads from /etc/fstab and spits its contents out to console\n\n");
	fprintf(stream, "  --version\n\tget the version of this tool\n\n");
	fprintf(stream, "  --help\n\tspits this helpful screen out\n\n");
	fprintf(stream, "  --author\n\tget information about me ;)\n\n");
	fprintf(stream, "  --about\n\ta little bit of background information about this project\n\n");
	fprintf(stream, "  --credits\n\ta list of the other people that have contributed in some way to this project\n\n");
	fprintf(stream, "\n");
}
