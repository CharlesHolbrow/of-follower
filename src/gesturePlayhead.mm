#include "gesturePlayhead.h"

void GesturePlayhead::init(Gesture* g) {
    gesture = g;
    playbackPoint = 0;
    playbackTime = 0;
};


Range<std::vector<Blip>::iterator> GesturePlayhead::play(double until) {
    int start = playbackPoint;
    int end = playbackPoint;
    while (gesture->blipsVec.size() > end) {
        // we know that gesture->blipsVec[end] exists
        if (gesture->blipsVec[end].gestureTime > until) break;
        end++;
    }
    playbackPoint = end;
    playbackTime = until;
    return Range<std::vector<Blip>::iterator>(gesture->blipsVec.begin() + start, gesture->blipsVec.begin() + end);
};

Range<std::vector<Blip>::iterator> GesturePlayhead::update(double delta) {
    return play(playbackTime + delta);
};
