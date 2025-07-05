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

#ifndef CONVEX_HULL_GRAHAM_SCAN1_H_
#define CONVEX_HULL_GRAHAM_SCAN1_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

bool fast_scan(Point points[], const size_t point_count, Point *convex_set_points[], size_t *convex_set_point_count);

#endif  // CONVEX_HULL_GRAHAM_SCAN1_H_
