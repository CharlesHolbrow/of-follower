#include "gesturePlayhead.h"

Range<std::vector<Blip>::iterator> GesturePlayhead::play(double until) {
    int start = playbackPoint;
    int end = playbackPoint;
    while (gesture->blipsVec.size() > end) {
        // we know that gesture->blipsVec[end] exists
        // check if we need to return, but increment anyway
        if (gesture->blipsVec[end].gestureTime > until) break;
        end++;
    }
    playbackPoint = end;
    return Range<std::vector<Blip>::iterator>(gesture->blipsVec.begin() + start, gesture->blipsVec.begin() + end);
};

GesturePlayhead::GesturePlayhead(Gesture* g) {
    gesture = g;
    playbackPoint = 0;
};
