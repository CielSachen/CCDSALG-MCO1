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
 * @file sort.c
 * @brief The source code containing the implementation of the sorting utility functions.
 * @copyright GNU AGPLv3
 */

#include "convex_hull/sort.h"

/**
 * @brief Swaps the values of two pointers.
 * @param[in,out] a The first pointer to swap the value of.
 * @param[in,out] b The second pointer to swap the value of.
 */
void swap(Point *a, Point *b) {
    const Point temporary = *a;
    *a = *b;
    *b = temporary;
}

/**
 * @brief Sorts points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This uses the selection sort algorithm to sort.
 * @param[in,out] points The points to sort.
 * @param point_count The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void selection_sort(Point points[], const size_t point_count, const Point *const anchor_point) {
    for (size_t i = 0; i < point_count - 1; i++) {
        size_t smallest_index = i;

        for (size_t j = i + 1; j < point_count; j++) {
            const Point *const sorted_point = &points[smallest_index];
            const double sorted_polar_angle = polar_angle(sorted_point, anchor_point);

            const Point *const unsorted_point = &points[j];
            const double unsorted_polar_angle = polar_angle(unsorted_point, anchor_point);

            if (unsorted_polar_angle < sorted_polar_angle ||
                (unsorted_polar_angle == sorted_polar_angle &&
                 distance(anchor_point, unsorted_point) < distance(anchor_point, sorted_point))) {
                smallest_index = j;
            }
        }

        if (smallest_index != i) {
            swap(&points[i], &points[smallest_index]);
        }
    }
}

/**
 * @brief Checks if a point is larger than another point.
 * @details This checks if the polar angle is greater, or if the distance is greater when the polar angles are equal.
 * @param[in] a The point to check.
 * @param[in] b The point to check against.
 * @param[in] anchor_point The anchor or origin point to use.
 * @return Whether the point is larger than the other point.
 */
bool is_larger(const Point *const a, const Point *const b, const Point *const anchor_point) {
    const double a_polar_angle = polar_angle(a, anchor_point);
    const double b_polar_angle = polar_angle(b, anchor_point);

    return a_polar_angle > b_polar_angle ||
           (a_polar_angle == b_polar_angle && distance(anchor_point, a) > distance(anchor_point, b));
}

/**
 * @brief Heapifies points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This swaps points until all "parent nodes" are larger than their children.
 * @param[in,out] points The points to heapify.
 * @param point_count The number of points to heapify.
 * @param root_index The index of the root point to use.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void heapify(Point points[], const size_t point_count, const size_t root_index, const Point *const anchor_point) {
    size_t largest_index = root_index;

    const size_t left_index = 2 * root_index + 1;

    if (left_index < point_count && is_larger(&points[left_index], &points[largest_index], anchor_point)) {
        largest_index = left_index;
    }

    const size_t rigth_index = 2 * root_index + 2;

    if (rigth_index < point_count && is_larger(&points[rigth_index], &points[largest_index], anchor_point)) {
        largest_index = rigth_index;
    }

    if (largest_index != root_index) {
        swap(&points[root_index], &points[largest_index]);

        heapify(points, point_count, largest_index, anchor_point);
    }
}

/**
 * @brief Sorts points by their polar angle, or distance if the polar angles are equal, in ascending order.
 * @details This uses the heap sort algorithm to sort.
 * @param[in,out] points The points to sort.
 * @param point_count The number of points to sort.
 * @param[in] anchor_point The anchor or origin point to use.
 */
void heap_sort(Point points[], const size_t point_count, const Point *const anchor_point) {
    for (int i = point_count / 2 - 1; i >= 0; i--) {
        heapify(points, point_count, i, anchor_point);
    }

    for (int i = point_count - 1; i > 0; i--) {
        swap(&points[0], &points[i]);

        heapify(points, i, 0, anchor_point);
    }
}
