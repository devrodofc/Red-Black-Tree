#ifndef CSV_H
#define CSV_H

#include <stddef.h>

void csv_create(
    const char *filename);

void csv_append_result(
    size_t input_size,
    double insert_time,
    double search_time,
    double delete_time);

void csv_close(void);

#endif