#pragma once

#include "gesture.h"

template <class Iter>
class Range {
    Iter b;
    Iter e;
public:
    Range(Iter b, Iter e) : b(b), e(e) {}
    Iter begin() { return b; }
    Iter end() { return e; }
};

struct GesturePlayhead {
    Gesture* gesture;
    int playbackPoint; // the last unreturned point
    GesturePlayhead(Gesture* g);
    Range<std::vector<Blip>::iterator> play(double until);
};