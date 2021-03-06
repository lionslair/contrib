#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"

#define FS_INODE_NR "/proc/sys/fs/inode-nr"

int open_inodes(int argc, char **argv) {
	FILE *f;
	int nr, freen;
	if(argc > 1) {
		if(!strcmp(argv[1], "config")) {
			puts("graph_title Inode table usage\n"
				"graph_args --base 1000 -l 0\n"
				"graph_vlabel number of open inodes\n"
				"graph_category system\n"
				"graph_info This graph monitors the Linux open inode table.\n"
				"used.label open inodes\n"
				"used.info The number of currently open inodes.\n"
				"max.label inode table size\n"
				"max.info The size of the system inode table. This is dynamically adjusted by the kernel.");
			print_warncrit("used");
			print_warncrit("max");
			return 0;
		}
		if(!strcmp(argv[1], "autoconf"))
			return autoconf_check_readable(FS_INODE_NR);
	}
	if(!(f=fopen(FS_INODE_NR, "r")))
		return fail("cannot open " FS_INODE_NR);
	if(2 != fscanf(f, "%d %d", &nr, &freen)) {
		fclose(f);
		return fail("cannot read from " FS_INODE_NR);
	}
	fclose(f);
	printf("used.value %d\nmax.value %d\n", nr-freen, nr);
	return 0;
}
