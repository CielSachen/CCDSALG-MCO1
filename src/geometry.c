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

#include "convex_hull/geometry.h"

#include <math.h>
#include <stdlib.h>

double distance(const Point *const a, const Point *const b) {
    return sqrt(pow(fabs(a->x - b->x), 2) + pow(fabs(a->y - b->y), 2));
}

double polar_angle(const Point *const point, const Point *const anchor_point) {
    const double angle = atan2(point->y - anchor_point->y, point->x - anchor_point->x);

    return isnan(angle) ? 0 : angle;
}

int orientation(const Point *const a, const Point *const b, const Point *const c) {
    const double area = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);

    return area < 0 ? -1 : area > 0 ? 1 : 0;
}
