#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

/* The name of this command. */
#define PROGRAM_NAME "aflk"

#define USAGE "\
Usage: aflk [OPTIONS] <filename>\n\n\
OPTIONS:\n\
    -S, --setlk       Set a lock using F_SETLK.\n\
    -W, --setlkw      Set a blocking lock using F_SETLKW.\n\
    -G, --getlk       Query the lock status using F_GETLK.\n\
    -t, --type        Specify the lock type (read or write). Default value is read.\n\
    -s, --start       Specify the starting byte of the lock as a numeric value. Default value is 0.\n\
    -w, --whence      Interpretation of l_start (set, cur, end). Default value is set.\n\
    -l, --len         Specify the number of bytes to lock. Default value is 0.\n\
    -h, --help        Display this help message.\n\n\
Examples:\n\
    aflk -S -t write filename.txt\n\
    aflk -G filename.txt\n\
"

/* Function prototype declaration */
void show_lock_info(struct flock *lock);
int parse_options(int argc, char *argv[], struct flock *lock, int *fcntlflag, char **filename);
int perform_lock_action(int fcntlflag, char *filename, struct flock *lock);
