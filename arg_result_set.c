#include "arg_result_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
res_init(result_set_t res) {
    res->arguments = (char*) malloc(sizeof(char));
    res->parameters = (char***) malloc(sizeof(char**));
    res->size = 0;
    res->parameter_size = (int*) malloc(sizeof(int));
}

void
res_print(result_set_t set) {
    for (int i = 0; i < set->size; ++i) {
        printf("-%c \t", set->arguments[i]);
        printf("%s", set->parameter_size[i] == 0 ? "{NONE}" : "{");
        for (int j = 0; j < set->parameter_size[i]; ++j) {
            printf("%s", set->parameters[i][j]);
            printf("%s", j != set->parameter_size[i] - 1 ? ", " : "");
        }
        printf("%s", set->parameter_size[i] == 0 ? "" : "}");
        printf("\n");
    }
}

void
res_add_argument(result_set_t res, char short_opt, int index) {            // TODO memsafe
    res->arguments = (char*) realloc(res->arguments, sizeof(char) * (index + 1));
    res->parameters = (char***) realloc(res->parameters, sizeof(char**) * (index + 1));
    res->parameter_size = (int*) realloc(res->parameter_size, sizeof(int) * (index + 1));
    res->parameters[index] = (char**) malloc(sizeof(char*));
    res->arguments[index] = short_opt;
    res->parameter_size[index] = 0;
    ++res->size;
}

void
res_add_parameter(result_set_t res, char* par, int index) {
    res->parameters[index] = (char**) realloc(res->parameters[index], sizeof(char*) * (res->parameter_size[index] + 1));
    if (res->parameters[index] == NULL) {
        fprintf(stderr, "Realloc failed!\n");
        exit(1);
    }
    res->parameters[index][res->parameter_size[index]] = malloc(sizeof(char) * strlen(par));
    strcpy(res->parameters[index][res->parameter_size[index]], par);
    ++res->parameter_size[index];
}
