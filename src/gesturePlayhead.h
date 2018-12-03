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
    double playbackTime;
    void init(Gesture* g);
    Range<std::vector<Blip>::iterator> play(double until);
    Range<std::vector<Blip>::iterator> update(double delta);
};
