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
	fprintf(stdout, "kerntool v0.9\n");
	fprintf(stdout, "by chronix\n");
	fprintf(stdout, "https://github.com/akachronix/kerntool\n");
	fprintf(stdout, "\n");
}

void help(FILE* stream) {

	fprintf(stream, "Arguments: \n");
	fprintf(stream, "  --kernel-slide\treads the kernel slide from a file dropped by unc0ver and spits its contents out to console\n");
	fprintf(stream, "  --cydia-log\t\treads from cydia.log and spits the file's contents out to console\n");
	fprintf(stream, "  --offsets\t\treads offsets from offsets.plist and spits their contents out to console\n");
	fprintf(stream, "  --block-domain\tenter a domain to block using hosts file\n");
	fprintf(stream, "  --hosts\t\treads from /etc/hosts and spits its contents out to console\n");
	fprintf(stream, "  --hostname\t\tgets device name\n");
	fprintf(stream, "  --uname\t\tgets kernel and general device information\n");
	fprintf(stream, "  --fstab\t\treads from /etc/fstab and spits its contents out to console\n");
	fprintf(stream, "  --version\t\tget the version of this tool\n");
	fprintf(stream, "  --help\t\tspits this helpful screen out\n");
	fprintf(stream, "\n");
}
