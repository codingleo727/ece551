#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use

void parse_story_file(FILE * s_file, catarray_t * cat_arr);
char * parse_blank_line(char ** p);
catarray_t * parse_word_file(FILE * w_file);
void add_word(category_t * arr, const char * word);
int parse_category_line(char * line, char ** category, char ** word);
int check_category_exists(catarray_t * cat_arr, char ** category);
void create_new_category(catarray_t * cat_arr, char ** category, char ** word);
void free_catarr(catarray_t * cat_arr);

#endif
