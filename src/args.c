#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "../include/args.h"
#include "../include/clock.h"

void print_help() {
    printf("Usage: mars-clock [options]\n");
    printf("Options:\n");
    printf("  -h, --help    Display this help message\n");
    printf("  -v, --version Display the version number\n");
    printf("\n");
    printf("If no options are provided, the Airy Mean Time (AMT) will be displayed.\n");
    printf("For more knowleage, you can get it from https://www.giss.nasa.gov/tools/mars24/help/notes.html in English, and from https://liughgood.github.io/GenhaoLog/nasa/mars/time/2024/12/14/note-Mars24-sunclock.html in Chinese.\n");
}

void print_version() {
    printf("mars-clock version 1.0.0\n");
}

int handle_args(int argc, char *argv[]) {
    if (argc == 1) {
        calculate_mars_time();
        return 0;
    }

    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "hv", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'v':
                print_version();
                return 0;
            default:
                print_help();
                return 1;
        }
    }
    print_help();
    return 1;
}
