#include <stdio.h>
#include <assert.h>
#include "../src/geometry.c"

struct Rational rational1 = {1, 1};
struct Rational rational2 = {2, 1};
struct Rational rational3 = {3, 2};

void test_intersection() {
    struct Point p1 = {.x = rational1, .y = rational1};
    struct Point p2 = {.x = rational2, .y = rational2};
    struct Point p3 = {.x = rational1, .y = rational2};
    struct Point p4 = {.x = rational2, .y = rational1};
    struct Point p5 = {.x = rational3, .y = rational3};
    struct Segment s1 = {.endpoint1 = &p1, .endpoint2 = &p2};
    struct Segment s2 = {.endpoint1 = &p3, .endpoint2 = &p4};

    printf("Testing intersection\n");
    struct Point * result = get_intersection_point(&s1, &s2); // Suppose que module1_function existe
    assert(eq(get_x(result), get_x(&p5)) && eq(get_y(result), get_y(&p5))); // Vérifie si le résultat attendu est correct
    printf("Test passed!\n");
}

void test_do_intersect() {
    struct Point p1 = {.x = rational1, .y = rational1};
    struct Point p2 = {.x = rational2, .y = rational2};
    struct Point p3 = {.x = rational1, .y = rational2};
    struct Point p4 = {.x = rational2, .y = rational1};
    struct Segment s1 = {.endpoint1 = &p1, .endpoint2 = &p3};
    struct Segment s2 = {.endpoint1 = &p2, .endpoint2 = &p4};
    struct Segment s3 = {.endpoint1 = &p1, .endpoint2 = &p3};
    struct Segment s4 = {.endpoint1 = &p2, .endpoint2 = &p4};
    struct Segment s5 = s1;

    int result = do_intersect(&s1, &s2);
    assert(result == 1);
    result = do_intersect(&s3, &s4);
    assert(result == 0);
    result = do_intersect(&s1, &s5);
    assert(result == 2);
}

int main() {
    test_do_intersect();
    test_intersection();
    return 0;
}
