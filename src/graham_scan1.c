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
 * @file graham_scan1.c
 * @brief The source code containing the implementation of the slow graham scan.
 * @copyright GNU AGPLv3
 */

#include "convex_hull/graham_scan1.h"

#include <stdio.h>
#include <time.h>

#include "convex_hull/sort.h"
#include "convex_hull/stack.h"

/**
 * @brief Scans points to find the points that would make up the convex hull using a slower sorting algorithm.
 * @details This locates the point with the lowest y-coordinate, and lowest x-coordinate if multiple, and sets it as the
 * anchor point. The points are sorted, using the selection sort algorithm. Then, they are checked one-by-one for the
 * direction of the angle they formed. All points, starting from the anchor point, that have a counter-clockwise
 * direction form the convex hull.
 * @param[in,out] points The points to scan through. This will be mutated to be sorted.
 * @param point_count The number of points to scan through.
 * @param[out] convex_set_points The resulting points from the created convex set.
 * @param[out] convex_set_point_count The number of resulting points from the created convex set.
 * @return Whether the scan was completed.
 */
bool slow_scan(Point points[], const size_t point_count, Point *convex_set_points[], size_t *convex_set_point_count) {
    const clock_t start_time = clock();

    size_t anchor_point_index = 0;

    for (size_t i = 1; i < point_count; i++) {
        Point *anchor_point = &points[anchor_point_index];
        Point *point = &points[i];

        if (point->y < anchor_point->y || (point->y == anchor_point->y && point->x < anchor_point->x)) {
            anchor_point_index = i;
        }
    }

    const Point anchor_point = points[anchor_point_index];

    selection_sort(points, point_count, &anchor_point);

    Stack stack;

    create(&stack);

    push(&stack, points[0]);
    push(&stack, points[1]);

    for (size_t i = 2; i < point_count; i++) {
        Point current_point = pop(&stack);
        const Point next_point = points[i];

        while (!is_empty(&stack) && orientation(top(&stack), &current_point, &next_point) <= 0) {
            current_point = pop(&stack);
        }

        push(&stack, current_point);

        if (is_full(&stack)) {
            printf("The stack has overflowed because of having too many points!\n");

            return false;
        }

        push(&stack, next_point);
    }

    const Point last_point = pop(&stack);

    if (orientation(top(&stack), &last_point, &anchor_point) > 0) {
        push(&stack, last_point);
    }

    *convex_set_points = stack.data;
    *convex_set_point_count = stack.top + 1;

    const clock_t end_time = clock();

    printf("Execution Time: %lfms\n", (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000);

    return true;
}
