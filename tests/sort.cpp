extern "C" {
#include "convex_hull/sort.h"
}

#include <gtest/gtest.h>

#include <algorithm>

#define ARRAY_LENGTH 10

Point POINTS[ARRAY_LENGTH] = {{7, 5}, {5, 8}, {8, 1}, {1, 6}, {6, 0}, {3, 9}, {9, 4}, {4, 10}, {8, 6}, {2, 0}};
Point *const ANCHOR_POINT = &POINTS[9];

TEST(Swap, SwapsValues) {
    const Point first_value = {0, 0};
    Point swappable_first_value = first_value;
    const Point second_value = {1, 1};
    Point swappable_second_value = second_value;

    swap(&swappable_first_value, &swappable_second_value);

    EXPECT_EQ(swappable_first_value.x, second_value.x);
    EXPECT_EQ(swappable_first_value.y, second_value.y);
    EXPECT_EQ(swappable_second_value.x, first_value.x);
    EXPECT_EQ(swappable_second_value.y, first_value.y);
}

TEST(SelectionSort, SortsElementsIntoIncreasingOrder) {
    Point array[ARRAY_LENGTH];

    std::copy(POINTS, POINTS + ARRAY_LENGTH, array);

    selection_sort(array, ARRAY_LENGTH, ANCHOR_POINT);

    for (std::size_t i = 0; i < ARRAY_LENGTH - 1; i++) {
        Point *current_point = &array[i];
        double current_polar_angle = polar_angle(current_point, ANCHOR_POINT);
        Point *next_point = &array[i + 1];
        double next_polar_angle = polar_angle(next_point, ANCHOR_POINT);

        if (current_polar_angle == next_polar_angle) {
            EXPECT_LT(distance(ANCHOR_POINT, current_point), distance(ANCHOR_POINT, next_point));
        } else {
            EXPECT_LT(current_polar_angle, next_polar_angle);
        }
    }
}

TEST(IsLarger, ReturnsTrueIfAHasLargerPolarAngle) {
    const Point *a = &POINTS[1];
    const Point *b = &POINTS[0];

    EXPECT_EQ(is_larger(a, b, ANCHOR_POINT), true);
}

TEST(IsLarger, ReturnsTrueIfAHasEqualPolarAngleAndLargerDistance) {
    const Point *a = &POINTS[8];
    const Point *b = &POINTS[0];

    EXPECT_EQ(is_larger(a, b, ANCHOR_POINT), true);
}

TEST(IsLarger, ReturnsFalseIfAHasSmallerPolarAngle) {
    const Point *a = &POINTS[0];
    const Point *b = &POINTS[1];

    EXPECT_EQ(is_larger(a, b, ANCHOR_POINT), false);
}

TEST(IsLarger, ReturnsFalseIfAHasEqualPolarAngleAndSmallerDistance) {
    const Point *a = &POINTS[0];
    const Point *b = &POINTS[8];

    EXPECT_EQ(is_larger(a, b, ANCHOR_POINT), false);
}

TEST(HeapSort, SortsElementsIntoIncreasingOrder) {
    Point array[ARRAY_LENGTH];

    std::copy(POINTS, POINTS + ARRAY_LENGTH, array);

    heap_sort(array, ARRAY_LENGTH, ANCHOR_POINT);

    for (std::size_t i = 0; i < ARRAY_LENGTH - 1; i++) {
        Point *current_point = &array[i];
        double current_polar_angle = polar_angle(current_point, ANCHOR_POINT);
        Point *next_point = &array[i + 1];
        double next_polar_angle = polar_angle(next_point, ANCHOR_POINT);

        if (current_polar_angle == next_polar_angle) {
            EXPECT_LT(distance(ANCHOR_POINT, current_point), distance(ANCHOR_POINT, next_point));
        } else {
            EXPECT_LT(current_polar_angle, next_polar_angle);
        }
    }
}
