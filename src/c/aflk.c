/*
Usage: aflk [OPTIONS] <filename>

OPTIONS:
  -S, --setlk       Set a lock using F_SETLK.
  -W, --setlkw      Set a blocking lock using F_SETLKW.
  -G, --getlk       Query the lock status using F_GETLK.
  -t, --type        Specify the lock type (read or write).
  -s, --start       Specify the starting byte of the lock.
  -w, --whence      Interpretation of l_start (set, cur, end).
  -l, --len         Specify the number of bytes to lock.

Examples:
  aflk -S -t write filename.txt
  aflk -G filename.txt

Note: Please refer to the documentation for detailed usage and examples.
*/
#include "aflk.h"

/* 
 * Display the help message showing how to use the program.
 */
void display_help()
{
    printf("Usage: %s [OPTIONS] <filename>\n\n", PROGRAM_NAME);
    printf("OPTIONS:\n");
    printf("  -S, --setlk       Set a lock using F_SETLK.\n");
    printf("  -W, --setlkw      Set a blocking lock using F_SETLKW.\n");
    printf("  -G, --getlk       Query the lock status using F_GETLK.\n");
    printf("  -t, --type        Specify the lock type (read or write). Default value is read.\n");
    printf("  -s, --start       Specify the starting byte of the lock. Default value is 0.\n");
    printf("  -w, --whence      Interpretation of l_start (set, cur, end). Default value is set.\n");
    printf("  -l, --len         Specify the number of bytes to lock. Default value is 0.\n");
    printf("  -h, --help        Display this help message.\n\n");
    printf("Examples:\n");
    printf("  aflk -S -t write filename.txt\n");
    printf("  aflk -G filename.txt\n\n");
    printf("Note: Please refer to the documentation for detailed usage and examples.\n");
}

/* 
 * Display the current status of the file lock.
 * @param lock: Pointer to a flock structure containing lock details.
 */
void show_lock_info(struct flock *lock)
{
/* Check if the file is not locked */
    if (lock->l_type == F_UNLCK)
    {
        printf("No locks held.\n");
    }
    else /* The file is locked */
    {
        /* Print lock information including type (Read/Write), start, and length of the lock */
        printf("Lock type: %s, Start: %lld, Length: %lld\n",
               /* Determine if it's a Read or Write lock */
               lock->l_type == F_RDLCK ? "Read" : "Write",
               /* Starting byte of the lock */
               (long long)lock->l_start,
               /* Number of bytes locked */
               (long long)lock->l_len);
    }
}

/* 
 * Parse command line options to set up the lock details, action, and filename.
 * @param argc: Number of command line arguments.
 * @param argv: Array of command line arguments.
 * @param lock: Pointer to a flock structure to be populated based on options.
 * @param fcntlflag: Pointer to an int to indicate which fcntl action to perform.
 * @param filename: Pointer to a char* to store the filename to be processed.
 * @return: 0 on successful parsing, 1 on any error.
 */
int parse_options(int argc, char *argv[], struct flock *lock, int *fcntlflag, char **filename)
{
    /* Define the long options for getopt_long */
    struct option long_options[] = {
        {"setlk", no_argument, 0, 'S'},
        {"setlkw", no_argument, 0, 'W'},
        {"getlk", no_argument, 0, 'G'},
        {"type", required_argument, 0, 't'},
        {"start", required_argument, 0, 's'},
        {"whence", required_argument, 0, 'w'},
        {"len", required_argument, 0, 'l'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};
    
    int option_index = 0;
    int c = -1;
    char *endptr = NULL;
    /* CounterFlags to check if the options -S, -W, or -G are set */
    int option_counter = 0;

    /* Loop through each option provided in the command arguments */
    while ((c = getopt_long(argc, argv, "SWGt:s:w:l:", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'S':
            *fcntlflag = F_SETLK;
            option_counter++;
            break;
        case 'W':
            *fcntlflag = F_SETLKW;
            option_counter++;
            break;
        case 'G':
            *fcntlflag = F_GETLK;
            option_counter++;
            break;
        case 't':
            if (strcmp(optarg, "read") == 0)
            {
                (*lock).l_type = F_RDLCK;
            }
            else if (strcmp(optarg, "write") == 0)
            {
                (*lock).l_type = F_WRLCK;
            }
            else
            {
                fprintf(stderr, "Invalid lock type: %s\n", optarg);
                return 1;
            }
            break;
        case 's':
            errno = 0;
            lock->l_start = strtol(optarg, &endptr, 10);
            if (errno != 0 || *endptr != '\0')
            {
                fprintf(stderr, "Invalid value for starting byte: %s\n", optarg);
                return 1;
            }
            break;
        case 'w':
            if (strcmp(optarg, "set") == 0)
            {
                (*lock).l_whence = SEEK_SET;
            }
            else if (strcmp(optarg, "cur") == 0)
            {
                (*lock).l_whence = SEEK_CUR;
            }
            else if (strcmp(optarg, "end") == 0)
            {
                (*lock).l_whence = SEEK_END;
            }
            else
            {
                fprintf(stderr, "Invalid whence value: %s\n", optarg);
                return 1;
            }
            break;
        case 'l':
            errno = 0;
            lock->l_len = strtol(optarg, &endptr, 10);
            if (errno != 0 || *endptr != '\0')
            {
                fprintf(stderr, "Invalid value for length: %s\n", optarg);
                return 1;
            }
            break;
        case 'h':
            display_help();
            return 0;
        default:
            /* Invalid option provided */
            fprintf(stderr, "Invalid option provided. Use -h or --help for usage information.\n");
            return 1;
        }
    }

    /* Check if the filename is provided */
    if (optind >= argc)
    {
        fprintf(stderr, "Specify a filename.\n");
        printf("\n");
        display_help();
        return 1;
    }

    /* Check if required options is specified */
    if (option_counter != 1)
    {
        fprintf(stderr, "You must specify only one of the following options: -S, -W, or -G.\n");
        printf("\n");
        display_help();
        return 1;
    }

    /* Assign the filename argument to the filename pointer */
    *filename = argv[optind];

    return 0;
}

/* 
 * Execute the appropriate file lock operation based on provided parameters.
 * @param fcntlflag: Flag to determine which fcntl action to perform.
 * @param filename: Name of the file to lock/unlock/query.
 * @param lock: Pointer to a flock structure containing lock details.
 * @return: 0 on successful operation, 1 on any error.
 */
int perform_lock_action(int fcntlflag, char *filename, struct flock *lock)
{
    int fd = 0;

    /* Reset the errno variable */
    errno = 0;

    /* Attempt to open the file for reading and writing */
    fd = open(filename, O_RDWR);
    if (fd == -1)
    {
        /* Output an error if the file fails to open */
        perror("Failed to open file");
        return 1;
    }

    /* Reset the errno variable */
    errno = 0;

    /* Attempt to set a lock using F_SETLK */
    if (fcntlflag == F_SETLK)
    {
        if (fcntl(fd, F_SETLK, lock) == -1)
        {
            /* Output an error if the lock fails */
            perror("Failed to set lock using F_SETLK");
            close(fd);
            return 1;
        }

        /* Inform the user that the file is locked and waiting for a signal */
        printf("File locked: %s\n", filename);
        printf("Waiting for signal to release. Press Ctrl+C to interrupt.\n");
        pause();  /* Pause execution until a signal is received */
    }
    /* Attempt to set a lock using F_SETLKW (waits for the lock if it's already held) */
    else if (fcntlflag == F_SETLKW)
    {
        if (fcntl(fd, F_SETLKW, lock) == -1)
        {
            /* Output an error if the lock fails */
            perror("Failed to set lock using F_SETLKW");
            close(fd);
            return 1;
        }

        /* Inform the user that the file is locked and waiting for a signal */
        printf("File locked: %s\n", filename);
        printf("Waiting for signal to release. Press Ctrl+C to interrupt.\n");
        pause();  /* Pause execution until a signal is received */
    }
    /* Attempt to retrieve lock information using F_GETLK */
    else if (fcntlflag == F_GETLK)
    {
        if (fcntl(fd, F_GETLK, lock) == -1)
        {
            /* Output an error if the retrieval of lock information fails */
            perror("Failed to get lock information");
            close(fd);
            return 1;
        }
        /* Display the lock information */
        show_lock_info(lock);
    }
    else
    {
        /* Inform the user that an invalid action was specified */
        fprintf(stderr, "Invalid action specified. Please choose one of the following options: -S/--setlk, -W/--setlkw, or -G/--getlk.\n");
        close(fd);
        return 1;
    }

    /* Close the file descriptor */
    close(fd);

    return 0;
}

int main(int argc, char *argv[])
{
    /* Initialize a flag for the fcntl action (e.g., F_SETLK, F_SETLKW, F_GETLK) */
    int fcntlflag = 0;
    /* Declare and initialize a struct for the file lock details */
    struct flock lock = {0};
    /* Pointer to hold the name of the file being processed */
    char *filename = NULL;

    /* Parse command line options to set up the lock struct, action flag, and filename */
    if (parse_options(argc, argv, &lock, &fcntlflag, &filename) != 0)
    {
        /* If there's an error in parsing options, exit with a failure status */
        return EXIT_FAILURE;
    }

    /* Perform the desired lock action based on parsed options */
    if (perform_lock_action(fcntlflag, filename, &lock) != 0)
    {
        /* If there's an error performing the lock action, exit with a failure status */
        return EXIT_FAILURE;
    }

    /* If all actions are successful, exit with a success status */
    return EXIT_SUCCESS;
}
