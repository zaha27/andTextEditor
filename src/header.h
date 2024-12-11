#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

void open_and_view_file(const char *filename);
void givehelp();
void give_edit(const char *x);
void give_insert(const char *x);
void give_advanced_insert(const char *x);

#endif
