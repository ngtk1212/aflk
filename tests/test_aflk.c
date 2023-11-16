#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>

#include "../src/h/aflk.h"
#include "../src/c/aflk.c"

void print_header(const char* func_name) {
    printf("-------------------------------------\n");
    printf("%s\n", func_name);
    printf("-------------------------------------\n");
}

/* -S */
void test_parse_options_normal_1() {
    char *argv[] = {"aflk", "-S", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_SETLK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -W */
void test_parse_options_normal_2() {
    char *argv[] = {"aflk", "-W", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_SETLKW);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -G */
void test_parse_options_normal_3() {
    char *argv[] = {"aflk", "-G", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -t write */
void test_parse_options_normal_4() {
    char *argv[] = {"aflk", "-G", "-t", "write", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_type of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_type, F_WRLCK);
    /* Except for the l_type of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -t read */
void test_parse_options_normal_5() {
    char *argv[] = {"aflk", "-G", "-t", "read", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_type of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    /* Except for the l_type of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -s */
void test_parse_options_normal_6() {
    char *argv[] = {"aflk", "-G", "-s", "10", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_start of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_start, 10);
    /* Except for the l_start of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -w set */
void test_parse_options_normal_7() {
    char *argv[] = {"aflk", "-G", "-w", "set", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_whence of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_whence, SEEK_SET);
    /* Except for the l_whence of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -w cur */
void test_parse_options_normal_8() {
    char *argv[] = {"aflk", "-G", "-w", "cur", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_whence of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_whence, SEEK_CUR);
    /* Except for the l_whence of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -w end */
void test_parse_options_normal_9() {
    char *argv[] = {"aflk", "-G", "-w", "end", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_whence of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_whence, SEEK_END);
    /* Except for the l_whence of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -l */
void test_parse_options_normal_10() {
    char *argv[] = {"aflk", "-G", "-l", "10", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is the specified value */
    CU_ASSERT_EQUAL(fcntlflag, F_GETLK);
    /* The l_len of lock is the specified value */
    CU_ASSERT_EQUAL(lock.l_len, 10);
    /* Except for the l_len of lock, this is the default value. */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    /* filename is the specified value */
    CU_ASSERT_STRING_EQUAL(filename, "filename.txt");
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -h */
void test_parse_options_normal_11() {
    char *argv[] = {"aflk", "-h"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended normaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 0);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is specified */
    CU_ASSERT_EQUAL(helpflag, 1);
}

/* invalid lock type (-t option value) */
void test_parse_options_error_1() {
    char *argv[] = {"aflk", "-t", "test", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* invalid value for starting byte (-s option value) */
void test_parse_options_error_2() {
    char *argv[] = {"aflk", "-s", "test", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* invalid whence value (-w option value) */
void test_parse_options_error_3() {
    char *argv[] = {"aflk", "-w", "test", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* invalid value for length (-l option value) */
void test_parse_options_error_4() {
    char *argv[] = {"aflk", "-l", "test", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* invalid option */
void test_parse_options_error_5() {
    char *argv[] = {"aflk", "-x", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* filename is not spacified */
void test_parse_options_error_6() {
    char *argv[] = {"aflk"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* -S, -W or -G is not spacified */
void test_parse_options_error_7() {
    char *argv[] = {"aflk", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    struct flock lock = {0};
    int fcntlflag = 0;
    char *filename = NULL;
    int helpflag = 0;

    /* init getopt_long */
    optind = 1;

    print_header(__func__);

    /* parse_options function ended abnormaly. */
    CU_ASSERT_EQUAL(parse_options(argc, argv, &lock, &fcntlflag, &filename, &helpflag), 1);
    /* fcntlflag is default */
    CU_ASSERT_EQUAL(fcntlflag, F_RDLCK);
    /* lock is default */
    CU_ASSERT_EQUAL(lock.l_type, F_RDLCK);
    CU_ASSERT_EQUAL(lock.l_start, 0);
    CU_ASSERT_EQUAL(lock.l_whence, 0);
    CU_ASSERT_EQUAL(lock.l_len, 0);
    /* filename is null */
    CU_ASSERT_PTR_NULL(filename);
    /* -h is not specified */
    CU_ASSERT_EQUAL(helpflag, 0);
}

/* lockable */
void test_get_lock_info_str_normal_1() {
    char str[256] = {'\0'};
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_UNLCK;

    get_lock_info_str(lock, str, sizeof(str));

    CU_ASSERT_STRING_EQUAL(str, "The file is lockable.\n");
}

/* Write locked */
void test_get_lock_info_str_normal_2() {
    char str[256] = {'\0'};
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_WRLCK;

    get_lock_info_str(lock, str, sizeof(str));

    CU_ASSERT_STRING_EQUAL(str, "The file is not lockable. The lock info of the file is type: Write, Start: 0, Length: 0.\n");
}

/* Read locked */
void test_get_lock_info_str_normal_3() {
    char str[256] = {'\0'};
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_RDLCK;

    get_lock_info_str(lock, str, sizeof(str));

    CU_ASSERT_STRING_EQUAL(str, "The file is not lockable. The lock info of the file is type: Read, Start: 0, Length: 0.\n");
}

/* Start value */
void test_get_lock_info_str_normal_4() {
    char str[256] = {'\0'};
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_RDLCK;
    lock.l_start = 100;

    get_lock_info_str(lock, str, sizeof(str));

    CU_ASSERT_STRING_EQUAL(str, "The file is not lockable. The lock info of the file is type: Read, Start: 100, Length: 0.\n");
}

/* Length value */
void test_get_lock_info_str_normal_5() {
    char str[256] = {'\0'};
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_RDLCK;
    lock.l_len = 100;

    get_lock_info_str(lock, str, sizeof(str));

    CU_ASSERT_STRING_EQUAL(str, "The file is not lockable. The lock info of the file is type: Read, Start: 0, Length: 100.\n");
}

/* Lock by F_SETLK */
void test_perform_lock_action_normal_1() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_WRLCK;

    CU_ASSERT_EQUAL(perform_lock_action(F_SETLK, "./test_output/dummy.txt", lock), 0);
}

/* Lock by F_SETLKW */
void test_perform_lock_action_normal_2() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_WRLCK;

    CU_ASSERT_EQUAL(perform_lock_action(F_SETLKW, "./test_output/dummy.txt", lock), 0);
}

/* Get lock info by F_GETLK */
void test_perform_lock_action_normal_3() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_WRLCK;

    CU_ASSERT_EQUAL(perform_lock_action(F_GETLK, "./test_output/dummy.txt", lock), 0);
}

/* Invalid filename */
void test_perform_lock_action_error_1() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_WRLCK;

    CU_ASSERT_EQUAL(perform_lock_action(F_SETLK, "aaaaaa", lock), 1);
}

/* F_SETLK lock failed */
void test_perform_lock_action_error_2() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = 999;

    CU_ASSERT_EQUAL(perform_lock_action(F_SETLK, "./test_output/dummy.txt", lock), 1);
}

/* F_SETLKW lock failed */
void test_perform_lock_action_error_3() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = 999;

    CU_ASSERT_EQUAL(perform_lock_action(F_SETLKW, "./test_output/dummy.txt", lock), 1);
}

/* F_GETLK failed to retrieve lock info */
void test_perform_lock_action_error_4() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = 999;

    CU_ASSERT_EQUAL(perform_lock_action(F_GETLK, "./test_output/dummy.txt", lock), 1);
}

/* Invalid fcntlflag */
void test_perform_lock_action_error_5() {
    struct flock lock = {0};

    print_header(__func__);

    lock.l_type = F_WRLCK;

    CU_ASSERT_EQUAL(perform_lock_action(999, "./test_output/dummy.txt", lock), 1);
}

/* main */
void test_main_normal_1() {
    char *argv[] = {"aflk", "-G", "./test_output/dummy.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    print_header(__func__);

    /* init getopt_long */
    optind = 1;

    CU_ASSERT_EQUAL(_main_for_cunit(argc, argv), 0);
}

/* --help */
void test_main_normal_2() {
    char *argv[] = {"aflk", "--help"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    print_header(__func__);

    /* init getopt_long */
    optind = 1;

    CU_ASSERT_EQUAL(_main_for_cunit(argc, argv), 0);
}

/* Failed option check on main  */
void test_main_error_1() {
    char *argv[] = {"aflk", "-X", "./test_output/dummy.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    print_header(__func__);

    /* init getopt_long */
    optind = 1;

    CU_ASSERT_EQUAL(_main_for_cunit(argc, argv), 1);
}

/* Failed lock on main */
void test_main_error_2() {
    char *argv[] = {"aflk", "-G", "filename.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    print_header(__func__);

    /* init getopt_long */
    optind = 1;

    CU_ASSERT_EQUAL(_main_for_cunit(argc, argv), 1);
}

#undef main
int main(void) {
    int ret;
    CU_pSuite suite;
    CU_initialize_registry();

    suite = CU_add_suite("Option test", NULL, NULL);
    CU_add_test(suite, "test_parse_options_normal_1", test_parse_options_normal_1);
    CU_add_test(suite, "test_parse_options_normal_2", test_parse_options_normal_2);
    CU_add_test(suite, "test_parse_options_normal_3", test_parse_options_normal_3);
    CU_add_test(suite, "test_parse_options_normal_4", test_parse_options_normal_4);
    CU_add_test(suite, "test_parse_options_normal_5", test_parse_options_normal_5);
    CU_add_test(suite, "test_parse_options_normal_6", test_parse_options_normal_6);
    CU_add_test(suite, "test_parse_options_normal_7", test_parse_options_normal_7);
    CU_add_test(suite, "test_parse_options_normal_8", test_parse_options_normal_8);
    CU_add_test(suite, "test_parse_options_normal_9", test_parse_options_normal_9);
    CU_add_test(suite, "test_parse_options_normal_10", test_parse_options_normal_10);
    CU_add_test(suite, "test_parse_options_normal_11", test_parse_options_normal_11);
    CU_add_test(suite, "test_parse_options_error_1", test_parse_options_error_1);
    CU_add_test(suite, "test_parse_options_error_2", test_parse_options_error_2);
    CU_add_test(suite, "test_parse_options_error_3", test_parse_options_error_3);
    CU_add_test(suite, "test_parse_options_error_4", test_parse_options_error_4);
    CU_add_test(suite, "test_parse_options_error_5", test_parse_options_error_5);
    CU_add_test(suite, "test_parse_options_error_6", test_parse_options_error_6);
    CU_add_test(suite, "test_parse_options_error_7", test_parse_options_error_7);

    suite = CU_add_suite("Lock info message test", NULL, NULL);
    CU_add_test(suite, "test_get_lock_info_str_normal_1", test_get_lock_info_str_normal_1);
    CU_add_test(suite, "test_get_lock_info_str_normal_2", test_get_lock_info_str_normal_2);
    CU_add_test(suite, "test_get_lock_info_str_normal_3", test_get_lock_info_str_normal_3);
    CU_add_test(suite, "test_get_lock_info_str_normal_4", test_get_lock_info_str_normal_4);
    CU_add_test(suite, "test_get_lock_info_str_normal_5", test_get_lock_info_str_normal_5);

    suite = CU_add_suite("Lock test", NULL, NULL);
    CU_add_test(suite, "test_perform_lock_action_normal_1", test_perform_lock_action_normal_1);
    CU_add_test(suite, "test_perform_lock_action_normal_2", test_perform_lock_action_normal_2);
    CU_add_test(suite, "test_perform_lock_action_normal_3", test_perform_lock_action_normal_3);
    CU_add_test(suite, "test_perform_lock_action_error_1", test_perform_lock_action_error_1);
    CU_add_test(suite, "test_perform_lock_action_error_2", test_perform_lock_action_error_2);
    CU_add_test(suite, "test_perform_lock_action_error_3", test_perform_lock_action_error_3);
    CU_add_test(suite, "test_perform_lock_action_error_4", test_perform_lock_action_error_4);
    CU_add_test(suite, "test_perform_lock_action_error_5", test_perform_lock_action_error_5);

    suite = CU_add_suite("Main test", NULL, NULL);
    CU_add_test(suite, "test_main_normal_1", test_main_normal_1);
    CU_add_test(suite, "test_main_normal_2", test_main_normal_2);
    CU_add_test(suite, "test_main_error_1", test_main_error_1);
    CU_add_test(suite, "test_main_error_2", test_main_error_2);

    CU_basic_run_tests();

    ret = CU_get_number_of_failures();

    CU_cleanup_registry();
    return ret;
}

