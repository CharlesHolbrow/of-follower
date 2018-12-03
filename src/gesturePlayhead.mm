#include "gesturePlayhead.h"

void GesturePlayhead::init(Gesture* g) {
    gesture = g;
    playbackIndex = 0;
    playbackTime = 0;
};

Range<std::vector<Blip>::iterator> GesturePlayhead::update(double delta) {
    double until = playbackTime + delta;
    int start = playbackIndex;
    int& end = playbackIndex; // lets call this 'end' for clarity

    // the !playbackComplete clause in the while condition ensures that we
    // do not return any blips past the end. If for some reason we want to play
    // past the end of the "terminated" Gesture, I believe we can just remove
    // `&& !playbackComplete()` from while condition.
    while (gesture->blipsVec.size() > end && !playbackComplete()) {
        // we know that blipsVec[end] exists
        // we know that blipsVec[end] was added before gesture termination
        if (gesture->blipsVec[end].gestureTime > until) break;
        // we know that blipsVec[end] time is <= until
        end++;
        // end (and playbackIndex) now point to the next blip to look at
    }
    // note that because `end` is a refernce to `playbackIndex`, we have been
    // updating playbackIndex inside the loop.
    playbackTime = until;
    return Range<std::vector<Blip>::iterator>(gesture->blipsVec.begin() + start, gesture->blipsVec.begin() + end);
};

bool GesturePlayhead::playbackComplete() {
    if (gesture->totalBlips < 0) return false; // gesture is still recording
    return playbackIndex >= gesture->totalBlips;
};
