//
//  gesture.h
//  Hike
//
//  Created by Charles Holbrow on 11/10/18.
//
// Gesture is a touch input recorder. It keeps a sequential, timestamped
// list of touch events.

#ifndef gesture_h
#define gesture_h

#include <list>

#include "ofMain.h"
#include "stepper.h"
#include "filter.h"

// A Blip on the radar. Timing and position of a point in the gesture.
struct Blip {
    ofVec2f pos;

    double gestureTime; // How long into the gesture was this created?
    double sinceTime;   // how long after step0 was this created?
    double updateTime;  // At the last step in the frame, how old is the blip?
};

class Gesture {
private:
    double updateStepsDuration; // duration of all steps in the most recent update
    ofVec2f previousPos;        // Mouse position at the end of last frame
    std::list <Blip> blips;
    Filter <60> filter;

public:
    // Starts a new gesture. (does not change stepper size)
    void start( ofVec2f pos) {
        previousPos = pos;
        updateStepsDuration = 0;
        filter.fill(pos);
        blips.clear();
    };

    // How long did the most recent update cover? Should be a multiple of step size.
    double getUpdateDuration() {
        return updateStepsDuration;
    };

    void update(Stepper stepper, ofVec2f pos) {
        ofVec2f mi = previousPos;     // initial mouse position
        ofVec2f mf = pos;             // final mouse position
        ofVec2f dm = mf - mi;         // mouse delta

        // velocity final. The unfiltered gesture looks prettier with stepsDuration
        // than with frameDuration
        ofVec2f vf = dm / stepper.stepsDuration();

        // Note that the step at "stepZeroTime" has already been processed.
        // For that reason, we start on stepIndex 1, and loop while "<="
        int stepIndex = 1; // start
        while (stepIndex <= stepper.steps) {
            // time since stepZero
            double sinceTime = stepIndex * stepper.stepSize;
            // time to next step zero
            double updateTime = stepper.stepsDuration() - sinceTime;

            ofVec2f input = mi + vf * sinceTime;
            filter.push(input);

            Blip b;
            b.pos = filter.average();
            b.updateTime = updateTime;
            b.sinceTime = sinceTime;
            b.gestureTime = stepper.stepZeroTime + sinceTime;

            blips.push_back(b);
            stepIndex++;
        }

        previousPos = mf;
    };

    int size() {
        return blips.size();
    };

    bool canPop() {
        return !blips.empty();
    };

    Blip pop() {
        Blip b;
        if (!canPop()) return b;

        b = blips.front();
        blips.pop_front();
        return b;
    };
};


#endif /* gesture_h */
