extern "C" {
#include "convex_hull/stack.h"
}

#include <gtest/gtest.h>

TEST(Create, SetsTopToNegativeOne) {
    Stack stack;

    create(&stack);

    EXPECT_EQ(stack.top, -1);
}

TEST(Push, AddsElementToEndOfArray) {
    Stack stack;

    create(&stack);

    Point element = {0, 0};

    push(&stack, element);

    Point *inserted_element = &stack.data[0];

    EXPECT_EQ(inserted_element->x, element.x);
    EXPECT_EQ(inserted_element->y, element.y);
}

TEST(Push, IncreasesTop) {
    Stack stack;

    create(&stack);

    Point element = {0, 0};

    push(&stack, element);

    EXPECT_EQ(stack.top, 0);
}

TEST(Pop, ReturnsLastElement) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_element = {1, 1};

    push(&stack, last_element);

    Point popped_element = pop(&stack);

    EXPECT_EQ(popped_element.x, last_element.x);
    EXPECT_EQ(popped_element.y, last_element.y);
}

TEST(Pop, DecreasesTop) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_element = {1, 1};

    push(&stack, last_element);

    pop(&stack);

    EXPECT_EQ(stack.top, 0);
}

TEST(Top, ReturnsLastElement) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_element = {1, 1};

    push(&stack, last_element);

    Point const *top_element = top(&stack);

    EXPECT_EQ(top_element->x, last_element.x);
    EXPECT_EQ(top_element->y, last_element.y);
}

TEST(Top, DoesNotMutateTop) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_element = {1, 1};

    push(&stack, last_element);

    top(&stack);

    EXPECT_EQ(stack.top, 1);
}

TEST(IsFull, ReturnsTrueIfTopIsMax) {
    Stack stack;

    create(&stack);

    for (std::size_t i = 0; i < MAX_STACK_SIZE; i++) {
        push(&stack, {0, 0});
    }

    EXPECT_EQ(is_full(&stack), true);
}

TEST(IsFull, ReturnsFalseIfTopIsNotMax) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    EXPECT_EQ(is_full(&stack), false);
}

TEST(IsEmpty, ReturnsTrueIfTopIsNegativeOne) {
    Stack stack;

    create(&stack);

    EXPECT_EQ(is_empty(&stack), true);
}

TEST(IsEmpty, ReturnsFalseIfTopIsNotNegative) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    EXPECT_EQ(is_empty(&stack), false);
}
