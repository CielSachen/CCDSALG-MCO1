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

#ifndef CONVEX_HULL_SORT_H_
#define CONVEX_HULL_SORT_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

void swap(Point *a, Point *b);

void selection_sort(Point points[], const size_t point_count, const Point *const anchor_point);

bool is_larger(const Point *const a, const Point *const b, const Point *const anchor_point);

void heapify(Point points[], const size_t point_count, const size_t root_index, const Point *const anchor_point);

void heap_sort(Point points[], const size_t point_count, const Point *const anchor_point);

#endif  // CONVEX_HULL_SORT_H_
