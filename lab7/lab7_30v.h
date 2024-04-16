#ifndef LAB7_30V_H
#define LAB7_30V_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct lib_write{
    int is_first;
    char name[50];
    char author[50];
    char place[50];
    char publishing_house[50];
    int year_of_publishing;
    int volume;
    struct lib_write *next; /* ссылка на следующий адрес */ 
    struct lib_write *prev; /* ссылка на предыдущий адрес */ 
}lib_write;

int input(lib_write *lib);
int count_works(lib_write *first_lib);
int count_volume(lib_write *first_lib);
int count_works_of_isd(lib_write *first_lib, char *publishing_house);
void find_of_author(lib_write *first_lib, char *author_phind);
void find_by_year(lib_write *first_lib, int year_phind);
lib_write *get_end_lib(lib_write * first_lib);
lib_write *Sort_for_year(lib_write *first_lib,  int (fptr)(lib_write *first_lib, lib_write *next_lib));
lib_write *Sort_for_author(lib_write *first_lib,  int (fptr)(lib_write *first_lib, lib_write *next_lib));
void swap(lib_write *lib1, lib_write *lib2);
int output(lib_write *first_lib);
int sort_year_big_to_small(lib_write *first_lib, lib_write *next_lib);
int sort_year_small_to_big(lib_write *first_lib, lib_write *next_lib);
int comparison_str_small_to_big(lib_write *lib1, lib_write *lib2);
int comparison_str_big_to_small(lib_write *lib1, lib_write *lib2);
int swap_neigborn(lib_write *lib1, lib_write *lib2);
lib_write *get_tail(lib_write *lib1);
lib_write * get_num_lib(lib_write *tail, int num);
lib_write *pop(lib_write *tail, int num);
lib_write * push(lib_write *tail, lib_write *new_elem, int num);
int get_size(lib_write *tail);
int get_all_adress(lib_write *tail);
int printf_struct(lib_write *tail, FILE *dst);
lib_write *scanf_new_struct(lib_write *tail, FILE* src);
lib_write *push_tail(lib_write *tail, lib_write *new_elem);
lib_write *add_obj(lib_write *result, int num);
void print_reajims();
int free_libs(lib_write *tail);
#endif
