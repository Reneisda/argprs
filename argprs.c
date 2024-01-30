#include "argprs.h"
#include "arg_result_set.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>



void
arg_init(arguments_t arg, const char* program_name, const char* version, int size) {
    arg->short_option = (char*) calloc(sizeof(char), size);
    arg->long_option = (char**) malloc(sizeof(char*) * size);
    arg->description = (char**) malloc(sizeof(char*) * size);
    arg->parameters = (uint8_t*) malloc(sizeof(uint8_t) * size);
    arg->PROGRAM_NAME = (char*) malloc(sizeof(char) * strlen(program_name));
    arg->VERSION = (char*) malloc(sizeof(char) * strlen(version));
    arg->size = size;
    strcpy(arg->PROGRAM_NAME, program_name);
    strcpy(arg->VERSION, version);
}

void
arg_add(arguments_t arg, char short_opt, char* long_opt, char* desc, uint8_t parameters) {
    if (short_opt == 0) {
        fprintf(stderr, "Short-option can't be '0'\n");
        exit(0);
    }

    int index;
    for (index = 0; arg->short_option[index] != 0; ++index);
    arg->short_option[index] = short_opt;
    arg->parameters[index] = parameters;
    arg->long_option[index] = (char*) malloc(sizeof(char) * strlen(long_opt));
    arg->description[index] = (char*) malloc(sizeof(char) * strlen(desc));
    strcpy(arg->long_option[index], long_opt);
    strcpy(arg->description[index], desc);
}

void
arg_parse(arguments_t arg, result_set_t result_set, int argc, char** argv) {
    int arg_index = 0;
    for (int i = 0; i < argc; ++i) {
        if (strlen(argv[i]) <= 1 || argv[i][0] != '-') {    // is argument?
            continue;
        }
        if (argv[i][1] == '-' && strlen(argv[i]) > 2) {     // long opt?
            // parse long opt?
        }
        else {
            for (int j = 0; j < arg->size; ++j) {               // short opt?
                if (arg->short_option[j] == argv[i][1]) {
                    res_add_argument(result_set, arg->short_option[j], arg_index);
                    for (int k = 0; k < arg->parameters[j]; ++k) {
                        if (arg->parameters[j] == result_set->parameter_size[arg_index]) {      // done for that agument
                            break;
                        }

                        if (i + k + 1 >= argc || argv[i + k + 1][0] == '-') {
                            fprintf(stderr, "Argument needs at least %d parameters\n", arg->parameters[j]);
                            exit(1);
                        }
                        res_add_parameter(result_set, argv[i + k + 1], arg_index);
                    }
                    ++arg_index;
                    i += arg->parameters[j];
                    break;
                }
            }
        }
    }
}

char
long_to_short_opt(arguments_t arg, char* long_opt) {   //TOBE optimise
    for (int i = 0; i < arg->size; ++i) {
        if (strcmp(arg->long_option[i], long_opt) == 0) {
            return arg->short_option[i];
        }
    }
    return '\0';
}


void
arg_print_help(arguments_t arg) {
    arg_print_program_version(arg);
    for (int i = 0; i < arg->size; ++i) {
        fprintf(stdout, "[-%c]\t", arg->short_option[i]);
        fprintf(stdout, "[--%s]\t", arg->long_option[i]);
        fprintf(stdout, "params:%d ", arg->parameters[i]);
        fprintf(stdout, "\"%s\"\n", arg->description[i]);
    }
}

void
arg_print_program_version(arguments_t arg) {
    fprintf(stdout, "%s ", arg->PROGRAM_NAME);
    fprintf(stdout, "%s\n", arg->VERSION);
}



