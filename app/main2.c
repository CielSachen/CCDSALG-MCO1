/*
 * Copyright (C) 2025  Raphael Panaligan  Jek Degullado
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file main1.c
 * @brief The source code containing the implementation of the convex hull program using a faster sorting algorithm.
 * @copyright GNU AGPLv3
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convex_hull/graham_scan2.h"
#include "convex_hull/stack.h"
#include "utils.h"

/** @brief The entry point of the convex hull program using a faster sorting algorithm. */
int main(void) {
    printf("Input File Name: ");

    String input_file_name;

    get_string_input(input_file_name, sizeof input_file_name);

    FILE *const input_file = fopen(input_file_name, "r");

    if (input_file == NULL) {
        perror("Failed to Read the Input File");

        return 1;
    }

    String input_buffer;

    int point_count;

    if (fgets(input_buffer, sizeof input_buffer, input_file) == NULL) {
        fclose(input_file);

        printf("The input file cannot be empty!\n");

        return 1;
    }

    sscanf(input_buffer, "%d", &point_count);

    const size_t points_memory_size = sizeof(Point) * point_count;

    if (points_memory_size > sizeof(Point) * MAX_STACK_SIZE) {
        fclose(input_file);

        printf("The problem size is too big! The application is at risk of a stack overflow error!");

        return 1;
    }

    Point *points = (Point *)malloc(points_memory_size);
    int actual_point_count = 0;

    while (fgets(input_buffer, sizeof input_buffer, input_file) != NULL) {
        Point *point = &points[actual_point_count++];

        sscanf(input_buffer, " %lf %lf", &point->x, &point->y);
    }

    fclose(input_file);

    if (actual_point_count != point_count) {
        free(points);

        printf("The problem size and the number of points do not match!\n");

        return 1;
    }

    printf("\n");

    Point *convex_set_points;
    size_t convex_set_point_count;

    if (!fast_scan(points, point_count, &convex_set_points, &convex_set_point_count)) {
        // The prior function already prints an error message.
        return 1;
    }

    free(points);

    printf("\n");

    printf("Output File Name: ");

    String output_file_name;

    get_string_input(output_file_name, sizeof output_file_name);

    FILE *const output_file = fopen(output_file_name, "w");

    if (output_file == NULL) {
        perror("Failed to Write the Output File");

        return 1;
    }

    print_convex_set_points(output_file, convex_set_points, convex_set_point_count);

    fclose(output_file);

    return 0;
}
