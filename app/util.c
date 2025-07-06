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
 * @file util.c
 * @brief The source code containing the implementation of the IO utility functions.
 * @copyright GNU AGPLv3
 */

#include "util.h"

#include <string.h>

/** @brief Clears the input buffer of all characters awaiting scanning. */
void clear_input_buffer(void) {
    int excess_character;

    while ((excess_character = getchar()) != '\n' && excess_character != EOF) {
    }
}

/**
 * @brief Gets a string typed input from the user.
 * @param[out] output The input received from the user.
 * @param max_length The maximum length of the output string.
 */
void get_string_input(char output[], const size_t max_length) {
    fflush(stdout);

    fgets(output, max_length, stdin);

    const size_t last_index = strlen(output) - 1;

    if (output[last_index] == '\n') {
        output[last_index] = '\0';
    } else {
        clear_input_buffer();
    }
}

/**
 * @brief Prints and formats points one-by-one into a text file.
 * @param[in] output_file The text file to print into.
 * @param[in] points The points to print.
 * @param point_count The number of points to print.
 */
void print_convex_set_points(FILE *const output_file, const Point points[], size_t point_count) {
    fprintf(output_file, "%ld\n", point_count);

    for (size_t i = 0; i < point_count; i++) {
        const Point *const point = &points[i];

        fprintf(output_file, "%11.6lf  %11.6lf\n", point->x, point->y);
    }
}
