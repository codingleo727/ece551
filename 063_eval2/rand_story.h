#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use

void add_word(category_t * arr, const char * word);
int parse_category_line(char * line, char ** category, char ** word);
int check_category_exists(catarray_t * cat_arr, char ** category);
void create_new_category(catarray_t * cat_arr, char ** category, char ** word);

#endif
