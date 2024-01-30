#ifndef PASSM_ARG_RESULT_SET_H
#define PASSM_ARG_RESULT_SET_H



typedef struct {
    char* arguments;
    char*** parameters;
    int size;
    int* parameter_size;
}
result_set_t[1];


void res_print(result_set_t set);
void res_add_argument(result_set_t res, char short_opt, int index);
void res_add_parameter(result_set_t res, char* par, int index);
void res_init(result_set_t res);

#endif //PASSM_ARG_RESULT_SET_H
