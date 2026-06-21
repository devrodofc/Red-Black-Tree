#include <stdio.h>
#include <stdlib.h>

#include "../include/csv.h"


static FILE *csv_file = NULL;


void csv_create(
    const char *filename)
{
    csv_file = fopen(
        filename,
        "w");

    if (csv_file == NULL)
    {
        fprintf(
            stderr,
            "Error creating CSV file: %s\n",
            filename);

        exit(EXIT_FAILURE);
    }

    fprintf(
        csv_file,
        "InputSize,InsertTime,SearchTime,DeleteTime\n");
}

void csv_append_result(
    size_t input_size,
    double insert_time,
    double search_time,
    double delete_time)
{
    if (csv_file == NULL)
    {
        fprintf(
            stderr,
            "CSV file not initialized.\n");

        exit(EXIT_FAILURE);
    }

    fprintf(
        csv_file,
        "%zu,%.12f,%.12f,%.12f\n",
        input_size,
        insert_time,
        search_time,
        delete_time);
}

void csv_close(void)
{
    if (csv_file != NULL)
    {
        fclose(csv_file);
        csv_file = NULL;
    }
}