#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

/* The name of this command. */
#define PROGRAM_NAME "aflk"

/* Function prototype declaration */
void display_help();
void show_lock_info(struct flock *lock);
int parse_options(int argc, char *argv[], struct flock *lock, int *fcntlflag, char **filename);
int perform_lock_action(int fcntlflag, char *filename, struct flock *lock);
