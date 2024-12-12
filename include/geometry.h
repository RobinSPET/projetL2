#pragma once

#include "../include/rational.h"

struct Point {
    struct Rational x; // abscisse
    struct Rational y; // ordonnée
};

struct Segment {
    struct Point * endpoint1;
    struct Point * endpoint2;
};